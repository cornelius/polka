/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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

#include "imageloader.h"

#include <QDebug>
#include <QTimer>

#include <KRandom>

ImageLoader::ImageLoader()
{
}

QPixmap ImageLoader::pixmap() const
{
  return m_pixmap;
}

void ImageLoader::setIdentity( const Polka::Identity &identity )
{
  m_identity = identity;
}

Polka::Identity ImageLoader::identity() const
{
  return m_identity;
}

void ImageLoader::load( const QUrl &url )
{
  setUrl( url );

  KJob *job = KIO::get( url, KIO::NoReload, KIO::HideProgressInfo );
  QObject::connect( job, SIGNAL( result( KJob * ) ),
    SLOT( slotResult( KJob * ) ) );
  QObject::connect( job, SIGNAL( data( KIO::Job *, const QByteArray & ) ),
    SLOT( slotData( KIO::Job *, const QByteArray & ) ) );
}

void ImageLoader::setUrl( const QUrl &url )
{
  m_url = url;
}

QUrl ImageLoader::url() const
{
  return m_url;
}

QUrl ImageLoader::profileUrl() const
{
  return QUrl();
}

void ImageLoader::slotResult( KJob *job )
{
  if ( job->error() ) {
    qWarning() << "Error retrieving image:" << url() << job->errorText();
    emit error( job->errorText() );
  } else {
    if ( !m_pixmap.loadFromData( m_data ) ) {
      qWarning() << "Unable to parse image data" << url();
    } else {
      if ( m_scaledSize.isValid() ) {
        m_pixmap = m_pixmap.scaled( m_scaledSize );
      }
      emit loaded( this );
    }
  }

  deleteLater();
}

void ImageLoader::slotData( KIO::Job *, const QByteArray &data )
{
  m_data.append( data );
}

void ImageLoader::setScaledSize( const QSize &size )
{
  m_scaledSize = size;
}

void ImageLoader::setPictureType( const QString &t )
{
  m_pictureType = t;
}

QString ImageLoader::pictureType() const
{
  return m_pictureType;
}

void ImageLoader::setUsername( const QString &username )
{
  m_username = username;
}

QString ImageLoader::username() const
{
  return m_username;
}

Polka::Picture ImageLoader::picture()
{
  Polka::Picture picture;
  picture.setId( KRandom::randomString( 10 ) );

  picture.setUrl( url().url() );
  picture.setPictureType( pictureType() );
  picture.setUsername( username() );

  return picture;
}
