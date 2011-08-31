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

#include "addpicturewidget.h"

#include "imageloadertwitter.h"
#include "imageloaderfacebook.h"

#include <KConfig>
#include <KMessageBox>
#include <KPushButton>
#include <KGlobal>
#include <KLocale>

AddPictureWidget::AddPictureWidget( PolkaModel *model, QWidget *parent )
  : QWidget( parent ), m_model( model )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  QPushButton *button;
  
  button = new QPushButton( i18n("Grab from screen") );
  connect( button, SIGNAL( clicked() ), SLOT( grabScreen() ) );
  topLayout->addWidget( button );

  QHBoxLayout *twitterLayout = new QHBoxLayout;
  topLayout->addLayout( twitterLayout );
  
  twitterLayout->addWidget( new QLabel( i18n("Twitter name:") ) );
  
  m_twitterNameEdit = new QLineEdit;
  twitterLayout->addWidget( m_twitterNameEdit );
  connect( m_twitterNameEdit, SIGNAL( returnPressed() ),
           SLOT( getTwitter() ) );
  
  button = new QPushButton( i18n("Get from Twitter") );
  connect( button, SIGNAL( clicked() ), SLOT( getTwitter() ) );
  twitterLayout->addWidget( button );
  
  QBoxLayout *facebookLayout = new QHBoxLayout;
  topLayout->addLayout( facebookLayout );
  
  facebookLayout->addWidget( new QLabel( i18n("Facebook name:") ) );
  
  m_facebookNameEdit = new QLineEdit;
  facebookLayout->addWidget( m_facebookNameEdit );
  connect( m_facebookNameEdit, SIGNAL( returnPressed() ),
           SLOT( getFacebook() ) );
  
  button = new QPushButton( i18n("Get from Facebook") );
  connect( button, SIGNAL( clicked() ), SLOT( getFacebook() ) );
  facebookLayout->addWidget( button );
  
  button = new QPushButton( i18n("Get from Google") );
  connect( button, SIGNAL( clicked() ), SLOT( getGoogle() ) );
  topLayout->addWidget( button );
}

AddPictureWidget::~AddPictureWidget()
{
}

void AddPictureWidget::show( const Polka::Identity &identity )
{
  Q_UNUSED( identity )
  
  // FIXME: show Twitter name, if known
  
  m_twitterNameEdit->clear();
  m_facebookNameEdit->clear();
  
  QWidget::show();
}

void AddPictureWidget::grabScreen()
{
  QTimer::singleShot( 0, this, SLOT( emitGrabPicture() ) );
}

void AddPictureWidget::emitGrabPicture()
{
  emit grabPicture();
}

void AddPictureWidget::getTwitter()
{
  ImageLoaderTwitter *loader;
  loader = ImageLoaderTwitter::load( m_twitterNameEdit->text() );
  connect( loader, SIGNAL( loaded( const QPixmap & ) ),
           SIGNAL( gotPicture( const QPixmap & ) ) );
}

void AddPictureWidget::getFacebook()
{
  ImageLoaderFacebook *loader;
  loader = ImageLoaderFacebook::load( m_facebookNameEdit->text() );
  connect( loader, SIGNAL( loaded( const QPixmap & ) ),
           SIGNAL( gotPicture( const QPixmap & ) ) );
}

void AddPictureWidget::getGoogle()
{
}
