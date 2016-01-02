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

#include "polkaversion.h"

#include <KAboutData>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>

static const char version[] = POLKA_VERSION;

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  KLocalizedString::setApplicationDomain("polka");

  KAboutData about( QStringLiteral("polka"), i18n("Polka"), version,
    i18n("The humane address book for the cloud"), KAboutLicense::GPL,
    i18n("(c) 2009-2015 Cornelius Schumacher"), QStringLiteral(),
    QStringLiteral("http://cornelius-schumacher.de/polka/"),
    QStringLiteral("schumacher@kde.org"));

  about.addAuthor(i18n("Cornelius Schumacher"), i18n("Creator"),
    QStringLiteral("schumacher@kde.org"));

  KAboutData::setApplicationData(about);

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  about.setupCommandLine(&parser);
  parser.process(app);
  about.processCommandLine(&parser);

  MainWindow *widget = new MainWindow;
  widget->show();

  return app.exec();
}
