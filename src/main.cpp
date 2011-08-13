/*
    This file is part of KDE.

    Copyright (C) 2009-2011 Cornelius Schumacher <schumacher@kde.org>

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

#include "mainwindow.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>

static const char description[] =
  I18N_NOOP("The humane address book for the cloud");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
  KAboutData about( "polka", 0, ki18n("Polka"), version, ki18n(description),
    KAboutData::License_GPL, ki18n("(C) 2011 Cornelius Schumacher"),
    KLocalizedString(), 0, "schumacher@kde.org" );
  about.addAuthor( ki18n("Cornelius Schumacher"), KLocalizedString(),
    "schumacher@kde.org" );
  KCmdLineArgs::init( argc, argv, &about );

  KApplication app;

  MainWindow *widget = new MainWindow;

  if ( app.isSessionRestored() ) {
    RESTORE(MainWindow);
  } else {
    widget->show();
  }

  return app.exec();
}
