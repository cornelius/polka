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

#include <KJob>
#include <kio/job.h>

#include <QUrl>
#include <QObject>
#include <QMap>
#include <QSize>
#include <QPixmap>

class ImageLoader : public QObject
{
    Q_OBJECT
  public:
    ImageLoader();

    void setIdentity( const Polka::Identity & );
    Polka::Identity identity() const;

    void setUrl( const QUrl & );
    QUrl url() const;

    virtual QUrl profileUrl() const;

    void setUsername( const QString & );
    QString username() const;

    void setScaledSize( const QSize & );

    void load( const QUrl & );

    QPixmap pixmap() const;

    Polka::Picture picture();

    void setPictureType( const QString & );
    QString pictureType() const;

  signals:
    void loaded( ImageLoader * );
    void error( const QString &text );

  protected slots:
    void slotResult( KJob *job );
    void slotData( KIO::Job *job, const QByteArray &data );

  private:
    Polka::Identity m_identity;
    QUrl m_url;
    QByteArray m_data;
    QSize m_scaledSize;
    QPixmap m_pixmap;
    QString m_pictureType;
    QString m_username;
};

#endif
