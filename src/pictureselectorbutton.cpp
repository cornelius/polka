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

#include "pictureselectorbutton.h"

#include "polkamodel.h"

#include <KLocalizedString>

#include <QBoxLayout>
#include <QLabel>

PictureSelectorButton::PictureSelectorButton( PolkaModel *model,
  QWidget *parent )
  : QWidget( parent ), m_model( model )
{
  QBoxLayout *topLayout = new QHBoxLayout( this );

  m_label = new QLabel;
  topLayout->addWidget( m_label );
  m_label->setAlignment( Qt::AlignCenter );
  m_label->setLineWidth( 1 );
  m_label->setMidLineWidth( 2 );

  setSelected( false );

  m_label->setFixedSize( 78, 78 );

  m_label->setText( i18n("Loading...") );
}

void PictureSelectorButton::setPicture( const Polka::Picture &picture )
{
  m_picture = picture;

  m_label->setPixmap( m_model->pixmap( picture ) );
}

void PictureSelectorButton::setSelected( bool selected )
{
  if ( selected ) {
    m_label->setFrameStyle( QFrame::Panel | QFrame::Sunken );
  } else {
    m_label->setFrameStyle( QFrame::Panel | QFrame::Raised );
  }
}

Polka::Picture PictureSelectorButton::picture() const
{
  return m_picture;
}

void PictureSelectorButton::setPixmap( const QPixmap &pixmap )
{
  m_label->setPixmap( pixmap );
}

void PictureSelectorButton::mousePressEvent( QMouseEvent *event )
{
  Q_UNUSED( event )

  emit picturePressed( m_picture );
}
