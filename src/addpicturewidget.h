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
#ifndef ADDPICTUREWIDGET_H
#define ADDPICTUREWIDGET_H

#include "polka/polka.h"
#include "polkamodel.h"

#include <QtGui>

class MatchList;

class AddPictureWidget : public QWidget
{
    Q_OBJECT
  public:
    AddPictureWidget( PolkaModel *, QWidget *parent = 0 );
    ~AddPictureWidget();

  signals:
    void grabPicture();
    
  protected slots:
    void grabScreen();
    void getTwitter();
    void getFacebook();
    void getGoogle();

  private slots:
    void emitGrabPicture();
    
  private:
    PolkaModel *m_model;
};

#endif
