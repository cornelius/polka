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

#include "localpicture.h"

#include "imageloader.h"

#include <KStandardDirs>

#include <QFile>
#include <QDir>
#include <QDebug>

LocalPicture::LocalPicture( GitDir *gitDir )
  : m_gitDir( gitDir )
{
  QString picPath = KStandardDirs::locate( "appdata", "polka_person.png" );
  // FIXME: Take default picture from static variable
  m_defaultPixmap = QPixmap( picPath );
}

void LocalPicture::setPicture( const Picture &picture )
{
  m_picture = picture;
}

QString LocalPicture::fullFilePath() const
{
  return m_gitDir->filePath( localFilePath() );
}

QString LocalPicture::localFilePath() const
{
  return "pictures/" + m_picture.id();
}

QPixmap LocalPicture::pixmap()
{
  if ( !m_pixmap.isNull() ) return m_pixmap;

  if ( m_picture.id().isEmpty() ) return m_defaultPixmap;

  if ( fileExists() ) {
    m_pixmap = QPixmap( fullFilePath() );
    return m_pixmap;
  }
  
  connect( ImageLoader::load( m_picture.url() ),
    SIGNAL( loaded( const QPixmap & ) ), SLOT( setPixmap( const QPixmap & ) ) );

  return m_defaultPixmap;
}

void LocalPicture::setPixmap( const QPixmap &pixmap )
{
  m_pixmap = pixmap;

  if ( !fileExists() ) {
    m_gitDir->addFile( localFilePath() );
    m_pixmap.save( fullFilePath(), "PNG" );
  }
  
  emit pixmapChanged( m_pixmap );
}

bool LocalPicture::fileExists() const
{
  return QFile::exists( fullFilePath() );
}