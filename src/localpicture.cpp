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

#include <KStandardDirs>
#include <KLocale>

#include <QFile>
#include <QDir>
#include <QDebug>

LocalPicture::LocalPicture( GitDir *gitDir, const Polka::Picture &picture )
  : m_gitDir( gitDir ), m_picture( picture )
{
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

  if ( m_picture.id().isEmpty() ) return QPixmap();

  if ( fileExists() ) {
    m_pixmap = scalePicture( QPixmap( fullFilePath() ) );
    return m_pixmap;
  }

  return QPixmap();
}

void LocalPicture::setPixmap( const QPixmap &pixmap,
  const Polka::Identity &identity )
{
  m_pixmap = scalePicture( pixmap );

  if ( !fileExists() ) {
    m_gitDir->createPath( localFilePath() );
    m_pixmap.save( fullFilePath(), "PNG" );
    m_gitDir->addFileWithoutCommit( localFilePath() );
  }
  
  emit pixmapChanged( m_pixmap );
}

bool LocalPicture::fileExists() const
{
  return QFile::exists( fullFilePath() );
}

QPixmap LocalPicture::scalePicture( const QPixmap &pixmap )
{
  int size = 70;

  if ( pixmap.width() <= size && pixmap.height() <= size ) {
    return pixmap;
  } else {
    return pixmap.scaled( size, size, Qt::KeepAspectRatio,
      Qt::SmoothTransformation );
  }
}
