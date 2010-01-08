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

#include "newpersondialog.h"

#include <KConfig>

NewPersonDialog::NewPersonDialog( PolkaModel *model, QWidget *parent )
  : KDialog( parent ), m_model( model )
{
  setCaption( "New Person" );
  setButtons( KDialog::Ok | KDialog::Cancel );
  setModal( true );

  QWidget *topWidget = new QWidget;
  
  QBoxLayout *topLayout = new QVBoxLayout( topWidget );

  QLabel *label = new QLabel( "Enter name of new person" );
  topLayout->addWidget( label );
  
  m_nameInput = new QLineEdit;
  topLayout->addWidget( m_nameInput );

  m_matchList = new QListView;
  topLayout->addWidget( m_matchList );
  m_matchList->setModel( m_model->allItemModel() );

  setMainWidget( topWidget );

  restoreDialogSize( KGlobal::config()->group("newpersondialog") );
}

NewPersonDialog::~NewPersonDialog()
{
  KConfigGroup cg( KGlobal::config(), "newpersondialog" );
  saveDialogSize( cg );
}

Identity NewPersonDialog::identity()
{
  Identity identity;
  
  identity.setDisplayName( m_nameInput->text() );

  return identity;
}