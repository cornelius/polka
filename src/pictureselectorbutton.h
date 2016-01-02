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
#ifndef PICTURESELECTORBUTTON_H
#define PICTURESELECTORBUTTON_H

#include "polka/polka.h"

#include <QWidget>

class PolkaModel;

class QLabel;

class PictureSelectorButton : public QWidget
{
    Q_OBJECT
  public:
    PictureSelectorButton( PolkaModel *model, QWidget *parent = 0 );

    void setPicture( const Polka::Picture & );

    Polka::Picture picture() const;

    void setSelected( bool selected );

  protected:
    void mousePressEvent( QMouseEvent *event );

  signals:
    void picturePressed( const Polka::Picture & );

  protected slots:
    void setPixmap( const QPixmap & );

  private:
    PolkaModel *m_model;

    Polka::Picture m_picture;

    QLabel *m_label;
};

#endif
