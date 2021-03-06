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
#ifndef IDENTITYITEM_H
#define IDENTITYITEM_H

#include "polka/polka.h"
#include "fanmenu.h"

#include <QtGui>

class PolkaModel;
class RoundedRectItem;

class IdentityItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

  public:
    IdentityItem( PolkaModel *, const Polka::Identity & );
    IdentityItem( QGraphicsItem *, PolkaModel *, const Polka::Identity & );

    Polka::Identity identity() const;

    void updateItem( const Polka::Identity & );

    void setDefaultPos( const QPointF & );
    QPointF defaultPos() const;

    void rememberPos( const QPointF & );
    QPointF rememberedPos() const;

    void hidePopups();

    void enableMenus( bool enabled );

    void undoMove();

  public slots:
    void checkItem();

  signals:
    void showGroup( const Polka::Identity & );
  
    void showIdentity( const Polka::Identity & );
    void removeIdentity( const Polka::Identity & );

    void itemMoved( IdentityItem *, const QPointF & );
    
    void itemChecked( const Polka::Identity &, bool );

    void menuShown();

    void itemDropped( IdentityItem * );

  protected:
    void init();
  
    void hoverEnterEvent( QGraphicsSceneHoverEvent *event );
    void hoverLeaveEvent( QGraphicsSceneHoverEvent *event );

    void mousePressEvent( QGraphicsSceneMouseEvent *event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );

    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event );

    QVariant itemChange( GraphicsItemChange change, const QVariant &value );

    bool hasPicture() const;

  protected slots:
    void emitRemoveIdentity();
    void emitShowIdentity();

  private:
    PolkaModel *m_model;
    Polka::Identity m_identity;

    bool m_menusEnabled;

    QPointF m_defaultPos;
    QPointF m_rememberedPos;
    bool m_checked;

    RoundedRectItem *m_nameItem;
    QGraphicsPathItem *m_checkItem;

    FanMenu *m_fanMenu;
    FanMenuItem *m_checkMenuItem;

    QPointF m_movePos;

    int m_itemSize;
};

#endif
