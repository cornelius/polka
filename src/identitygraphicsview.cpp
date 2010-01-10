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

#include "identitygraphicsview.h"

#include "polkamodel.h"
#include "polkaitemmodel.h"
#include "personview.h"

#include <KLocale>

IdentityGraphicsView::IdentityGraphicsView( PolkaModel *model, QWidget *parent )
  : QWidget( parent ), m_model( model )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  QBoxLayout *buttonLayout = new QHBoxLayout;
  topLayout->addLayout( buttonLayout );

  // FIXME: Use proper icon
  m_backButton = new QPushButton( "<" );
  buttonLayout->addWidget( m_backButton );
  connect( m_backButton, SIGNAL( clicked() ), SIGNAL( goBack() ) );

  buttonLayout->addStretch( 1 );

  m_groupNameLabel = new QLabel;
  buttonLayout->addWidget( m_groupNameLabel );

  buttonLayout->addStretch( 1 );

  QPushButton *button = new QPushButton( i18n("New Person") );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SIGNAL( newPerson() ) );

  m_scene = new QGraphicsScene;

  QGraphicsView *view = new QGraphicsView( m_scene );
  topLayout->addWidget( view );
  view->show();
}

void IdentityGraphicsView::setGroup( const Identity &group )
{
  m_group = group;

  setGroupName( group.displayName() );

  createItems();
}

void IdentityGraphicsView::createItems()
{
  m_scene->clear();

  Identity::List identities = m_model->identityList( m_group.id() );

  int columns = sqrt( identities.size() );
  int itemSize = 110;
  int spacing = 150;

  int x = 0;
  int y = 0;

  QGraphicsItem *item;

  foreach( Identity identity, identities ) {
    int posX = x * spacing + ( y % 2 ) * spacing / 2;
    int posY = y * spacing;

    item = m_scene->addEllipse( -itemSize/2, -itemSize/2,
      itemSize, itemSize );
    item->setPos( posX, posY );
  
    QPixmap pixmap = m_model->picture( identity );
  
    item = m_scene->addPixmap( m_model->picture( identity ) );
    item->setPos( posX - pixmap.width() / 2 , posY - pixmap.height() / 2 );
    
    x++;
    
    if ( x >= ( columns + ( y + 1 ) % 2 ) ) {
      x = 0;
      y++;
    }
  }
}

Identity IdentityGraphicsView::group() const
{
  return m_group;
}

void IdentityGraphicsView::setGroupName( const QString &name )
{
  m_groupNameLabel->setText( "<b>" + name + "</b>" );
}