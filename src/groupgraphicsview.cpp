/*
    This file is part of KDE.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "groupgraphicsview.h"

#include "polkamodel.h"
#include "polkaitemmodel.h"
#include "personview.h"
#include "identityitem.h"
#include "labelitem.h"
#include "trackinggraphicsview.h"
#include "mainmenuitem.h"
#include "magicmenuitem.h"
#include "settings.h"
#include "groupadderitem.h"

#include <KLocalizedString>
#include <KRandom>

#include <QInputDialog>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QLabel>

GroupGraphicsView::GroupGraphicsView( PolkaModel *model, QWidget *parent )
  : GroupView( model, parent ), m_mainMenu( 0 ), m_magicMenu( 0 ),
    m_groupAdderItem( 0 ), m_newLabelItem( 0 ), m_compactLayout( false ),
    m_morphToAnimation( 0 ), m_morphFromAnimation( 0 ),
    m_removeItemsAnimation( 0 ), m_placeItemsAnimation( 0 ),
    m_unplaceItemsAnimation( 0 ), m_unhideItemsAnimation( 0 )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_scene = new QGraphicsScene;
//  m_scene->setBackgroundBrush( Qt::red );
  m_scene->setBackgroundBrush( QColor( 70,70,100 ) );
  m_scene->setSceneRect( -3000, -3000, 6000, 6000 );

  m_view = new TrackingGraphicsView( m_scene );
  m_view->setRenderHint( QPainter::Antialiasing );
  topLayout->addWidget( m_view );
  m_view->show();
  connect( m_view, SIGNAL( viewportMoved() ), SLOT( positionAbsoluteItems() ) );

  connect( model, SIGNAL( identityAdded( const Polka::Identity & ) ),
    SLOT( slotIdentityAdded( const Polka::Identity & ) ) );
  connect( model, SIGNAL( identityChanged( const Polka::Identity & ) ),
    SLOT( slotIdentityChanged( const Polka::Identity & ) ) );
  connect( model, SIGNAL( identityRemoved( const Polka::Identity & ) ),
    SLOT( slotIdentityRemoved( const Polka::Identity & ) ) );

  createMenuItems();
  positionMenuItems();

  setMinimumWidth( 50 );
}

void GroupGraphicsView::slotIdentityChanged( const Polka::Identity &identity )
{
  IdentityItem *i = item( identity );

  if ( identity.groups().findGroup( group().id() ).isValid() && i ) {
    i->updateItem( identity );
  } else {
    recreateItems();
  }
}

void GroupGraphicsView::slotIdentityAdded( const Polka::Identity &identity )
{
  Q_UNUSED( identity )

  recreateItems();
}

void GroupGraphicsView::slotIdentityRemoved( const Polka::Identity &identity )
{
  Q_UNUSED( identity )

  recreateItems();
}

void GroupGraphicsView::recreateItems()
{
  m_previousItem = 0;
  placeItems();
}

void GroupGraphicsView::setCompactLayout( bool enabled )
{
  if ( enabled == m_compactLayout ) return;

  m_compactLayout = enabled;

  if ( m_compactLayout ) morphToCompact();
  else morphFromCompact();
}

void GroupGraphicsView::doShowGroup()
{
  m_previousItem = 0;

  if ( m_removeItemsAnimation ) m_removeItemsAnimation->stop();
  if ( m_placeItemsAnimation ) m_placeItemsAnimation->stop();
  if ( m_unplaceItemsAnimation ) m_unplaceItemsAnimation->stop();
  if ( m_unhideItemsAnimation ) m_unhideItemsAnimation->stop();

  if ( group().isValid() ) {
    m_previousItem = item( group() );
  }

  if ( m_previousItem ) {
    hideItems();
  } else {
    if ( m_items.isEmpty() ) {
      placeItems();
    } else {
      unplaceItems();
    }
  }
}

void GroupGraphicsView::hideItems()
{
  if ( !m_removeItemsAnimation ) {
    m_removeItemsAnimation = new QParallelAnimationGroup( this );
    connect( m_removeItemsAnimation, SIGNAL( finished() ),
      SLOT( placeItems() ) );
  }
  m_removeItemsAnimation->clear();

  foreach( IdentityItem *item, m_items ) {
    if ( item == m_previousItem ) continue;

    QPropertyAnimation *animation = new QPropertyAnimation(item, "opacity", this);
    m_removeItemsAnimation->insertAnimation( 0, animation );
    animation->setStartValue( 1 );
    animation->setEndValue( 0 );
    animation->setDuration( 200 );
  }

  m_removeItemsAnimation->start();
}

void GroupGraphicsView::clearItems()
{
  foreach( IdentityItem *item, m_items ) {
    delete item;
  }
  m_items.clear();

  foreach( LabelItem *item, m_labelItems ) {
    delete item;
  }
  m_labelItems.clear();
}

void GroupGraphicsView::placeItems()
{
  m_compactLayout = false;

  bool doAnimation = false;
  QPoint previousItemPos;

  if ( m_previousItem ) {
    doAnimation = true;

    if ( !m_placeItemsAnimation ) {
      m_placeItemsAnimation = new QParallelAnimationGroup( this );
      connect( m_placeItemsAnimation, SIGNAL( finished() ),
        SLOT( finishPlaceItems() ) );
    }
    m_placeItemsAnimation->clear();
    m_placeItemsAnimations.clear();

    previousItemPos = m_view->mapFromScene( m_previousItem->pos() );
  }

  clearItems();

  ItemGroup items = prepareItems( doAnimation );

  m_items = items.identityItems;
  m_labelItems = items.labelItems;
  foreach( IdentityItem *item, m_items ) {
    m_scene->addItem( item );
  }

  m_view->centerOn( items.center );

  if ( doAnimation ) {
    foreach( QPropertyAnimation *animation, m_placeItemsAnimations ) {
      animation->setStartValue( m_view->mapToScene( previousItemPos ) );
    }

    m_placeItemsAnimation->start();
  } else {
    foreach( LabelItem *item, m_labelItems ) {
      m_scene->addItem( item );
    }
  }

  foreach( IdentityItem *item, m_items ) {
    item->hidePopups();
  }
}

void GroupGraphicsView::finishPlaceItems()
{
  foreach( LabelItem *item, m_labelItems ) {
    m_scene->addItem( item );
  }
}

void GroupGraphicsView::unplaceItems()
{
  foreach( LabelItem *item, m_labelItems ) {
    delete item;
  }
  m_labelItems.clear();

  m_compactLayout = false;

  if ( !m_unplaceItemsAnimation ) {
    m_unplaceItemsAnimation = new QParallelAnimationGroup( this );
    connect( m_unplaceItemsAnimation, SIGNAL( finished() ),
      SLOT( unhideItems() ) );
  }
  m_unplaceItemsAnimation->clear();

  m_newItems = prepareItems( false );

  if ( !m_newItems.previousGroup ) {
    recreateItems();
    return;
  }

  QPointF target = m_newItems.previousGroup->pos();

  QRect viewportRect = m_view->viewport()->rect();
  QPoint currentViewportCenter( viewportRect.width() / 2,
    viewportRect.height() / 2 );
  QPointF currentCenter = m_view->mapToScene( currentViewportCenter );

  target.setX( target.x() - m_newItems.center.x() + currentCenter.x() );
  target.setY( target.y() - m_newItems.center.y() + currentCenter.y() );

  foreach( IdentityItem *item, m_items ) {
    QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);
    m_unplaceItemsAnimation->insertAnimation( 0, animation );

    animation->setDuration( 300 );
    animation->setEndValue( target );
    animation->setEasingCurve( QEasingCurve::OutCubic );
  }

  m_unplaceItemsAnimation->start();
}

void GroupGraphicsView::unhideItems()
{
  clearItems();

  m_items = m_newItems.identityItems;
  foreach( IdentityItem *item, m_items ) {
    item->setOpacity( 0 );
    m_scene->addItem( item );
  }

  m_labelItems = m_newItems.labelItems;
  foreach( LabelItem *item, m_labelItems ) {
    m_scene->addItem( item );
  }

  m_view->centerOn( m_newItems.center );

  if ( !m_unhideItemsAnimation ) {
    m_unhideItemsAnimation = new QParallelAnimationGroup( this );
  }
  m_unhideItemsAnimation->clear();

  foreach( IdentityItem *item, m_items ) {
    if ( item == m_newItems.previousGroup ) {
      item->setOpacity( 1 );
    } else {
      QPropertyAnimation *animation = new QPropertyAnimation(item, "opacity", this);
      m_unhideItemsAnimation->insertAnimation( 0, animation );
      animation->setStartValue( 0 );
      animation->setEndValue( 1 );
      animation->setDuration( 200 );
    }
  }

  m_newItems = ItemGroup();

  m_unhideItemsAnimation->start();
}

ItemGroup GroupGraphicsView::prepareItems( bool doAnimation )
{
  ItemGroup result;

  Polka::Identity::List identities = model()->identitiesOfGroup( group() );

  int columns = sqrt( identities.size() );
  int spacing = 150;

  int x = 0;
  int y = 0;

  qreal minX = 0;
  qreal minY = 0;
  qreal maxX = 0;
  qreal maxY = 0;

  bool firstItem = true;

  Polka::GroupView view = model()->groupView( group() );

  foreach( Polka::Identity identity, identities ) {
    qreal posX = x * spacing + ( y % 2 ) * spacing / 2;
    qreal posY = y * spacing * 0.866; // sin(60 degree)

    IdentityItem *item = new IdentityItem( model(), identity );
    result.identityItems.append( item );

    connect( item, SIGNAL( showIdentity( const Polka::Identity & ) ),
      SIGNAL( showIdentity( const Polka::Identity & ) ) );
    connect( item, SIGNAL( removeIdentity( const Polka::Identity & ) ),
      SLOT( slotRemoveIdentity( const Polka::Identity & ) ) );

    connect( item, SIGNAL( itemMoved( IdentityItem *, const QPointF & ) ),
      SLOT( savePosition( IdentityItem *, const QPointF & ) ) );
    connect( item, SIGNAL( itemChecked( const Polka::Identity &, bool ) ),
      SLOT( saveCheck( const Polka::Identity &, bool ) ) );

    item->setDefaultPos( QPointF( posX, posY ) );

    qreal itemX;
    qreal itemY;

    Polka::IdentityPosition p = view.findIdentityPosition( identity.id() );
    if ( p.isValid() ) {
      itemX = p.x();
      itemY = p.y();
    } else {
      itemX = posX;
      itemY = posY;
    }

    if ( doAnimation ) {
      QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);
      m_placeItemsAnimation->insertAnimation( 0, animation );
      m_placeItemsAnimations.append( animation );

      animation->setDuration( 300 );
      QPointF target( itemX, itemY );
      animation->setEndValue( target );
      animation->setEasingCurve( QEasingCurve::OutCubic );
    } else {
      item->setPos( itemX, itemY );
    }

    if ( firstItem ) {
      firstItem = false;

      minX = itemX;
      minY = itemY;
      maxX = itemX;
      maxY = itemY;
    } else {
      if ( itemX < minX ) minX = itemX;
      if ( itemY < minY ) minY = itemY;
      if ( itemX > maxX ) maxX = itemX;
      if ( itemY > maxY ) maxY = itemY;
    }

    Polka::IdentityCheck c = view.findIdentityCheck( identity.id() );
    if ( c.isValid() ) {
      item->checkItem();
    }

    x++;

    if ( x >= ( columns + ( y + 1 ) % 2 ) ) {
      x = 0;
      y++;
    }

    if ( previousGroup().isValid() &&
         item->identity().id() == previousGroup().id() ) {
      result.previousGroup = item;
    }
  }

  foreach( Polka::ViewLabel label, view.viewLabelList() ) {
    LabelItem *labelItem = createLabelItem( label );
    result.labelItems.append( labelItem );

    QRectF r = labelItem->sceneBoundingRect();

    if ( r.x() < minX ) minX = r.x();
    if ( r.x() + r.width() > maxX ) maxX = r.x() + r.width();
    if ( r.y() < minY ) minY = r.y();
    if ( r.y() + r.height() > maxY ) maxY = r.y() + r.height();
  }

  qreal centerX = ( minX + maxX ) / 2;
  qreal centerY = ( minY + maxY ) / 2;

  result.center = QPointF( centerX, centerY );

  return result;
}

void GroupGraphicsView::createMenuItems()
{
  if ( Settings::enableMagic() ) {
    m_magicMenu = new MagicMenuItem();
    m_scene->addItem( m_magicMenu );

    connect( m_magicMenu, SIGNAL( resetLayout() ), SLOT( resetLayout() ) );
    connect( m_magicMenu, SIGNAL( showSettings() ), SIGNAL( showSettings() ) );
  }

  m_mainMenu = new MainMenuItem();
  m_scene->addItem( m_mainMenu );

  connect( m_mainMenu, SIGNAL( cloneGroup() ), SLOT( emitCloneGroup() ) );
  connect( m_mainMenu, SIGNAL( removeGroup() ), SLOT( emitRemoveGroup() ) );
  connect( m_mainMenu, SIGNAL( addGroup() ), SIGNAL( newGroup() ) );
  connect( m_mainMenu, SIGNAL( addPerson() ), SIGNAL( newPerson() ) );

  m_groupAdderItem = new GroupAdderItem( model() );
  m_scene->addItem( m_groupAdderItem );
  m_groupAdderItem->setZValue( -100 );

  Polka::ViewLabel label;
  label.setText( i18n("New Label") );
  m_newLabelItem = new LabelItem( model(), label );
  m_newLabelItem->setMenuEnabled( false );
  m_scene->addItem( m_newLabelItem );

  connect( m_newLabelItem, SIGNAL( itemMoved( const Polka::ViewLabel &,
    const QPointF & ) ), SLOT(  newLabelMoved( const Polka::ViewLabel &,
    const QPointF & ) ) );
}

void GroupGraphicsView::positionMenuItems()
{
  QRect viewportRect = m_view->viewport()->rect();

  QPoint upperRight( viewportRect.width(), 0 );
  QPointF upperRightScene = m_view->mapToScene( upperRight );

  QPoint lowerLeft( 0, viewportRect.height() );
  QPointF lowerLeftScene = m_view->mapToScene( lowerLeft );

  if ( m_mainMenu ) {
    m_mainMenu->setPos( upperRightScene.x() - 50, upperRightScene.y() + 50 );
  }
  if ( m_magicMenu ) {
    m_magicMenu->setPos( upperRightScene.x() - 130, upperRightScene.y() + 50 );
  }
  if ( m_groupAdderItem ) {
    m_groupAdderItem->setPos( lowerLeftScene );
  }
  if ( m_newLabelItem ) {
    m_newLabelItem->setPos( upperRightScene.x() - 10,
      upperRightScene.y() + 130 );
  }
}

void GroupGraphicsView::positionAbsoluteItems()
{
  positionMenuItems();
}

void GroupGraphicsView::slotRemoveIdentity( const Polka::Identity &identity )
{
  emit removeIdentity( identity, group() );
}

void GroupGraphicsView::savePosition( IdentityItem *item,
  const QPointF &pos )
{
  if ( !m_compactLayout ) {
    if ( item->collidesWithItem( m_groupAdderItem ) ) {
      item->undoMove();
      model()->addIdentity( item->identity(), m_groupAdderItem->group() );
    } else {
      model()->saveViewPosition( group(), item->identity(), pos );
    }
  }
}

void GroupGraphicsView::saveLabel( const Polka::ViewLabel &label,
  const QPointF &pos )
{
  Polka::ViewLabel l = label;
  l.setX( pos.x() );
  l.setY( pos.y() );
  model()->saveViewLabel( group(), l );
}


void GroupGraphicsView::saveCheck( const Polka::Identity &identity,
  bool checked )
{
  model()->saveViewCheck( group(), identity, checked );
}

void GroupGraphicsView::newLabelMoved( const Polka::ViewLabel &,
  const QPointF &pos )
{
  addLabel( pos );

  positionMenuItems();
}

void GroupGraphicsView::addLabel()
{
  addLabel( m_view->mapToScene( QPoint( 10, 10 ) ) );
}

void GroupGraphicsView::addLabel( const QPointF &pos )
{
  bool ok;
  QString name = QInputDialog::getText( this, i18n("Add Label"),
    i18n("Enter text of label"), QLineEdit::Normal, QString(),
    &ok );
  if ( ok ) {
    Polka::ViewLabel label;
    label.setId( KRandom::randomString( 10 ) );
    label.setText( name );

    label.setX( pos.x() );
    label.setY( pos.y() );

    LabelItem *item = createLabelItem( label );
    m_scene->addItem( item );
    m_labelItems.append( item );

    model()->saveViewLabel( group(), label );
  }
}

void GroupGraphicsView::removeLabel( LabelItem *item )
{
  m_labelItems.removeAll( item );

  delete item;
  model()->removeViewLabel( group(), item->label() );
}

void GroupGraphicsView::renameLabel( LabelItem *item )
{
  Polka::ViewLabel label = item->label();

  bool ok;
  QString name = QInputDialog::getText( this, i18n("Rename Label"),
    i18n("Enter new text of label"), QLineEdit::Normal, label.text(),
    &ok );
  if ( ok ) {
    label.setText( name );
    item->setLabel( label );
    model()->saveViewLabel( group(), label );
  }
}

LabelItem *GroupGraphicsView::createLabelItem( const Polka::ViewLabel &label )
{
  LabelItem *item = new LabelItem( model(), label );

  connect( item, SIGNAL( itemMoved( const Polka::ViewLabel &, const QPointF & ) ),
    SLOT( saveLabel( const Polka::ViewLabel &, const QPointF & ) ) );
  connect( item, SIGNAL( removeLabel( LabelItem * ) ),
    SLOT( removeLabel( LabelItem * ) ) );
  connect( item, SIGNAL( renameLabel( LabelItem * ) ),
    SLOT( renameLabel( LabelItem * ) ) );

  item->setPos( label.x(), label.y() );

  return item;
}

void GroupGraphicsView::resetLayout()
{
  model()->clearViewPositions( group() );

  foreach( IdentityItem *item, m_items ) {
    if ( item->pos() != item->defaultPos() ) {
#if QT_VERSION >= 0x040600
      QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);

      animation->setDuration(500);
      animation->setStartValue( item->pos() );
      animation->setEndValue( item->defaultPos() );
      animation->setEasingCurve( QEasingCurve::OutCubic );

      animation->start();
#else
      item->setPos( item->defaultPos() );
#endif
    }
  }
}

void GroupGraphicsView::emitCloneGroup()
{
  emit cloneGroup( group() );
}

void GroupGraphicsView::emitRemoveGroup()
{
  emit removeGroup( group() );
}

void GroupGraphicsView::morphToCompact()
{
  m_mainMenu->hide();
  if ( m_magicMenu ) m_magicMenu->hide();
  if ( m_newLabelItem ) m_newLabelItem->hide();
  foreach( LabelItem *item, m_labelItems ) {
    item->hide();
  }
  m_groupAdderItem->hide();

  QPointF leftBorder = m_view->mapToScene( 0, 0 );

  int x = leftBorder.x() + 60;
  int y = leftBorder.y() + 60;
  int spacing = 60;

  if ( !m_morphToAnimation ) {
    m_morphToAnimation = new QParallelAnimationGroup( this );
    connect( m_morphToAnimation, SIGNAL( finished() ),
      SIGNAL( morphedToCompact() ) );
    connect( m_morphToAnimation, SIGNAL( finished() ),
      SLOT( finishMorphToCompact() ) );
  }
  m_morphToAnimation->clear();

  foreach( IdentityItem *item, m_items ) {
    QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);
    m_morphToAnimation->insertAnimation( 0, animation );

    animation->setDuration(500);
    item->rememberPos( item->pos() );
    animation->setStartValue( item->pos() );
    QPointF target( x, y );
    animation->setEndValue( target );
    animation->setEasingCurve( QEasingCurve::OutCubic );

    animation = new QPropertyAnimation(item, "scale", this );
    m_morphToAnimation->insertAnimation( 0, animation );

    animation->setDuration( 300 );
    animation->setStartValue( item->scale() );
    animation->setEndValue( 0.5 );
    animation->setEasingCurve( QEasingCurve::OutCubic );

    y += spacing;
  }

  m_morphToAnimation->start();
}

void GroupGraphicsView::finishMorphToCompact()
{
}

void GroupGraphicsView::morphFromCompact()
{
  if ( !m_morphFromAnimation ) {
    m_morphFromAnimation = new QParallelAnimationGroup( this );
    connect( m_morphFromAnimation, SIGNAL( finished() ),
      SIGNAL( morphedFromCompact() ) );
    connect( m_morphFromAnimation, SIGNAL( finished() ),
      SLOT( finishMorphFromCompact() ) );
  }
  m_morphFromAnimation->clear();

  foreach( IdentityItem *item, m_items ) {
    QPropertyAnimation *animation = new QPropertyAnimation(item, "pos", this);
    m_morphFromAnimation->insertAnimation( 0, animation );

    animation->setDuration(500);
    animation->setStartValue( item->pos() );
    animation->setEndValue( item->rememberedPos() );
    animation->setEasingCurve( QEasingCurve::OutCubic );

    animation = new QPropertyAnimation(item, "scale", this );
    m_morphFromAnimation->insertAnimation( 0, animation );

    animation->setDuration( 300 );
    animation->setStartValue( item->scale() );
    animation->setEndValue( 1 );
    animation->setEasingCurve( QEasingCurve::OutCubic );
  }

  m_morphFromAnimation->start();
}

void GroupGraphicsView::finishMorphFromCompact()
{
  m_mainMenu->show();
  if ( m_magicMenu ) m_magicMenu->show();
  if ( m_newLabelItem ) m_newLabelItem->show();

  foreach( LabelItem *item, m_labelItems ) {
    item->show();
  }

  m_groupAdderItem->show();
}

IdentityItem *GroupGraphicsView::item( const Polka::Identity &identity ) const
{
  foreach( IdentityItem *item, m_items ) {
    if ( item->identity().id() == identity.id() ) return item;
  }
  return 0;
}

void GroupGraphicsView::setAdderGroup( const Polka::Identity &group )
{
  m_groupAdderItem->setGroup( group );
}
