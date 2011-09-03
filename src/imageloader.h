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
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <polka/polka.h>

#include <KUrl>
#include <KJob>
#include <kio/job.h>

#include <QObject>
#include <QMap>

class ImageLoader : public QObject
{
    Q_OBJECT
  public:  
    ImageLoader();

    void setIdentity( const Polka::Identity & );
    Polka::Identity identity() const;
    
    void setUrl( const KUrl & );
    KUrl url() const;

    void setScaledSize( const QSize & );
    
    void load( const KUrl & );
    
    QPixmap pixmap() const;
    
  signals:
    void loaded( ImageLoader * );
    void error( const QString &text );

  protected slots:
    void slotResult( KJob *job );
    void slotData( KIO::Job *job, const QByteArray &data );

  private:
    Polka::Identity m_identity;
    KUrl m_url;
    QByteArray m_data;
    QSize m_scaledSize;
    QPixmap m_pixmap;
};

#endif
