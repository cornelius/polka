/*
    This file is part of KDE.

    Copyright (C) 2011 Cornelius Schumacher <schumacher@kde.org>

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

#include "pictureselectorcontrols.h"

#include "settings.h"
#include "polkamodel.h"

#include <KLocalizedString>

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

PictureSelectorControls::PictureSelectorControls( PolkaModel *model,
  QWidget *parent)
  : QWidget( parent ), m_model( model )
{
  QBoxLayout *topLayout = new QHBoxLayout( this );

  m_pictureLabel = new QLabel;
  topLayout->addWidget( m_pictureLabel );

  QBoxLayout *middleLayout = new QVBoxLayout;
  topLayout->addLayout( middleLayout );

  m_urlLabel = new QLabel;
  middleLayout->addWidget( m_urlLabel );

  middleLayout->addStretch( 1 );

  QBoxLayout *controlsLayout = new QHBoxLayout;
  middleLayout->addLayout( controlsLayout );

  QPushButton *button = new QPushButton( i18n("Make default") );
  controlsLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( makeDefault() ) );

  button = new QPushButton( i18n("Remove picture") );
  controlsLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( removePicture() ) );

  controlsLayout->addStretch( 1 );

  topLayout->addStretch( 1 );

  QBoxLayout *hideLayout = new QVBoxLayout;
  topLayout->addLayout( hideLayout );

  button = new QPushButton( i18n("Hide Settings") );
  hideLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( hide() ) );

  hideLayout->addStretch( 1 );
}

PictureSelectorControls::~PictureSelectorControls()
{
}

void PictureSelectorControls::setIdentity( const Polka::Identity &identity )
{
  m_identity = identity;
}

void PictureSelectorControls::setPicture( const Polka::Picture &picture )
{
  m_picture = picture;

  m_pictureLabel->setPixmap( m_model->pixmap( picture ) );

  QString t = picture.pictureType();
  if ( t.isEmpty() ) {
    m_urlLabel->setText( picture.url() );
  } else {
    QString txt = t;
    if ( t == "twitter" ) {
      txt = "Twitter";
    } else if ( t == "facebook" ) {
      txt = "Facebook";
    } else if ( t == "grabbed" ) {
      txt = i18n("Grabbed from screen");
    }
    m_urlLabel->setText( "<b>" + txt + "</b>" );
  }
}

Polka::Picture PictureSelectorControls::picture() const
{
  return m_picture;
}

void PictureSelectorControls::makeDefault()
{
  m_model->setDefaultPicture( m_picture, m_identity );
}

void PictureSelectorControls::removePicture()
{
  m_model->removePicture( m_picture, m_identity );

  hide();
}
