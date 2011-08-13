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

#include "overview.h"

#include <KLocale>
#include <KStandardDirs>

Overview::Overview()
{
  QBoxLayout *topLayout = new QHBoxLayout( this );


  QBoxLayout *buttonLayout = new QVBoxLayout;
  buttonLayout->setSpacing( 20 );

  buttonLayout->addStretch( 1 );

  QPushButton *button = new QPushButton( i18n("Back to group view") );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SIGNAL( showGroupView() ) );

  button = new QPushButton( i18n("History") );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SIGNAL( showHistory() ) );

  buttonLayout->addStretch( 1 );


  QBoxLayout *infoLayout = new QVBoxLayout;

  QString logoPath = KStandardDirs::locate( "appdata", "polka-logo.png" );
  QPixmap logoPixmap = QPixmap( logoPath );

  QLabel *logo = new QLabel;
  logo->setPixmap( logoPixmap );
  infoLayout->addWidget( logo );

  QLabel *about = new QLabel;
  about->setOpenExternalLinks( true );
  infoLayout->addWidget( about );
  
  QString text = "<qt>";
  text += i18n("Polka - the humane address book for the cloud");
  text += "<br/>";
  text += "<br/>";
  text += "Copyright (c) 2011 Cornelius Schumacher";
  text += "<br/>";
  text += "This program is distributed under the terms of the ";
  text += "<a href=\"http://gpl.org\">GPL</a>";
  text += "<br/>";
  text += "<br/>";
  text += "<a href=\"http://www.lst.de/~cs/polka\">http://www.lst.de/~cs/polka</a>";
  text += "</qt>";

  about->setText( text );


  topLayout->addStretch( 1 );
  topLayout->addLayout( infoLayout );
  topLayout->addStretch( 1 );
  topLayout->addLayout( buttonLayout );
  topLayout->addStretch( 1 );
}
