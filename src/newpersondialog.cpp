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

#include "matchlist.h"

#include <KConfig>
#include <KMessageBox>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

NewPersonDialog::NewPersonDialog( PolkaModel *model, QWidget *parent )
  : QDialog( parent ), m_model( model ), m_proxyModel( 0 ), m_matchList( 0 )
{
  setWindowTitle( "New Person" );

  setModal( true );

  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  m_okButton = buttonBox->button(QDialogButtonBox::Ok);
  m_okButton->setDefault(true);
  m_okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  QBoxLayout *topLayout = new QVBoxLayout( this );

  QLabel *label = new QLabel( "Enter name of new person" );
  topLayout->addWidget( label );

  m_nameInput = new QLineEdit;
  topLayout->addWidget( m_nameInput );
  connect( m_nameInput, SIGNAL( textChanged( const QString & ) ),
    SLOT( checkOkButton() ) );

  m_matchList = new MatchList( m_model );
  topLayout->addWidget( m_matchList );

  connect( m_matchList, SIGNAL( activated() ), SLOT( accept() ) );
  connect( m_nameInput, SIGNAL( textChanged( const QString & ) ),
    m_matchList, SLOT( filter( const QString & ) ) );

  topLayout->addWidget( buttonBox );

  KConfigGroup cg = KSharedConfig::openConfig()->group("NewPersonDialog");
  KWindowConfig::restoreWindowSize( windowHandle(), cg );

  m_nameInput->setFocus();

  checkOkButton();
}

NewPersonDialog::~NewPersonDialog()
{
  KConfigGroup cg = KSharedConfig::openConfig()->group("NewPersonDialog");
  KWindowConfig::saveWindowSize( windowHandle(), cg );
}

Polka::Identity NewPersonDialog::identity()
{
  if ( !m_matchList || !m_matchList->identity().isValid() ) {
    Polka::Identity identity;
    Polka::Name name;
    name.setValue( m_nameInput->text() );
    identity.setName( name );
    return identity;
  } else {
    return m_matchList->identity();
  }
}

void NewPersonDialog::checkOkButton()
{
  m_okButton->setEnabled( !m_nameInput->text().isEmpty() );
}
