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
  QGridLayout *topLayout = new QGridLayout( this );

  QPushButton *button;
  
  button = new QPushButton( i18n("Grab from screen") );
  connect( button, SIGNAL( clicked() ), SLOT( grabScreen() ) );
  topLayout->addWidget( button, 0, 2 );

  topLayout->addWidget( new QLabel( i18n("Twitter name:") ), 1, 0,
    Qt::AlignRight );
  
  m_twitterNameEdit = new QLineEdit;
  topLayout->addWidget( m_twitterNameEdit, 1, 1 );
  connect( m_twitterNameEdit, SIGNAL( returnPressed() ),
           SLOT( getTwitter() ) );
  
  button = new QPushButton( i18n("Get from Twitter") );
  connect( button, SIGNAL( clicked() ), SLOT( getTwitter() ) );
  topLayout->addWidget( button, 1, 2 );
  
  topLayout->addWidget( new QLabel( i18n("Facebook name:") ), 2, 0,
    Qt::AlignRight );
  
  m_facebookNameEdit = new QLineEdit;
  topLayout->addWidget( m_facebookNameEdit, 2, 1 );
  connect( m_facebookNameEdit, SIGNAL( returnPressed() ),
           SLOT( getFacebook() ) );
  
  button = new QPushButton( i18n("Get from Facebook") );
  connect( button, SIGNAL( clicked() ), SLOT( getFacebook() ) );
  topLayout->addWidget( button, 2, 2 );
}

AddPictureWidget::~AddPictureWidget()
{
}

void AddPictureWidget::show( const Polka::Identity &identity )
{
  m_identity = identity;
  
  m_twitterNameEdit->setText( m_model->link( identity, "twitter" ).username() );
  m_facebookNameEdit->setText( m_model->link( identity, "facebook" ).username() );
  
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
  ImageLoaderTwitter *loader = new ImageLoaderTwitter;
  loader->setIdentity( m_identity );
  loader->load( m_twitterNameEdit->text() );
  connect( loader, SIGNAL( loaded( ImageLoader * ) ),
           SIGNAL( gotPicture( ImageLoader * ) ) );
}

void AddPictureWidget::getFacebook()
{
  ImageLoaderFacebook *loader = new ImageLoaderFacebook;
  loader->setIdentity( m_identity );
  loader->load( m_facebookNameEdit->text() );
  connect( loader, SIGNAL( loaded( ImageLoader * ) ),
           SIGNAL( gotPicture( ImageLoader * ) ) );
}
