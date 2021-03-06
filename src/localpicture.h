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
#ifndef LOCALPICTURE_H
#define LOCALPICTURE_H

#include "polka/polka.h"
#include "gitdir.h"

#include <QPixmap>

class LocalPicture : public QObject
{
    Q_OBJECT
  public:
    LocalPicture( GitDir *, const Polka::Picture & );

    QPixmap pixmap();

    QString fullFilePath() const;

  public slots:
    void setPixmap( const QPixmap &pixmap, const Polka::Identity &identity );

  signals:
    void pixmapChanged( const QPixmap & );

  protected:
    QString localFilePath() const;

    bool fileExists() const;

    QPixmap scalePicture( const QPixmap & );

  private:
    GitDir *m_gitDir;

    Polka::Picture m_picture;

    QPixmap m_pixmap;
};

#endif
