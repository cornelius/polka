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

#include "addpicturedialog.h"

#include "matchlist.h"

#include <KConfig>
#include <KMessageBox>
#include <KPushButton>
#include <KGlobal>
#include <KLocale>

AddPictureDialog::AddPictureDialog( PolkaModel *model, QWidget *parent )
  : KDialog( parent ), m_model( model )
{
  setCaption( "AddPicture" );
  setButtons( KDialog::Close );
  setModal( true );

  QWidget *topWidget = new QWidget;
  setMainWidget( topWidget );
  
  QBoxLayout *topLayout = new QVBoxLayout( topWidget );

  QPushButton *button;
  
  button = new QPushButton( i18n("Grab from screen") );
  connect( button, SIGNAL( clicked() ), SLOT( grabScreen() ) );
  topLayout->addWidget( button );
  
  button = new QPushButton( i18n("Get from Twitter") );
  connect( button, SIGNAL( clicked() ), SLOT( getTwitter() ) );
  topLayout->addWidget( button );
  
  button = new QPushButton( i18n("Get from Facebook") );
  connect( button, SIGNAL( clicked() ), SLOT( getFacebook() ) );
  topLayout->addWidget( button );
  
  restoreDialogSize( KGlobal::config()->group("AddPictureDialog") );
}

AddPictureDialog::~AddPictureDialog()
{
  KConfigGroup cg( KGlobal::config(), "AddPictureDialog" );
  saveDialogSize( cg );
}

void AddPictureDialog::grabScreen()
{
  QTimer::singleShot( 0, this, SLOT( emitGrabPicture() ) );
  accept();
}

void AddPictureDialog::emitGrabPicture()
{
  emit grabPicture();
}

void AddPictureDialog::getTwitter()
{
}

void AddPictureDialog::getFacebook()
{
}
