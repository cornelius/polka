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

#include "newgroupdialog.h"

#include <KConfig>
#include <KMessageBox>
#include <KWindowConfig>
#include <KSharedConfig>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QListView>
#include <QLabel>

NewGroupDialog::NewGroupDialog( PolkaModel *model, QWidget *parent )
  : QDialog( parent ), m_model( model ), m_proxyModel( 0 ), m_matchList( 0 )
{
  setWindowTitle( "New Group" );

  setModal( true );

  QWidget *topWidget = new QWidget;

  QBoxLayout *topLayout = new QVBoxLayout( topWidget );

  QLabel *label = new QLabel( "Enter name of new group" );
  topLayout->addWidget( label );

  m_nameInput = new QLineEdit;
  topLayout->addWidget( m_nameInput );
  connect( m_nameInput, SIGNAL( textChanged( const QString & ) ),
    SLOT( checkOkButton() ) );

  if ( !m_model->groups().isEmpty() ) {
    m_matchList = new QListView;

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setFilterCaseSensitivity( Qt::CaseInsensitive );

    topLayout->addWidget( m_matchList );
    connect( m_matchList, SIGNAL( activated( const QModelIndex & ) ),
      SLOT( accept() ) );

    m_proxyModel->setSourceModel( m_model->groupItemModel() );
    m_matchList->setModel( m_proxyModel );

    connect( m_nameInput, SIGNAL( textChanged( const QString & ) ),
      m_proxyModel, SLOT( setFilterWildcard( const QString & ) ) );
  }

  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  topLayout->addWidget( buttonBox );

  m_okButton = buttonBox->button(QDialogButtonBox::Ok);
  m_okButton->setDefault(true);
  m_okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  KConfigGroup cg = KSharedConfig::openConfig()->group("NewGroupDialog");
  KWindowConfig::restoreWindowSize( windowHandle(), cg );

  m_nameInput->setFocus();

  checkOkButton();
}

NewGroupDialog::~NewGroupDialog()
{
  KConfigGroup cg = KSharedConfig::openConfig()->group("NewGroupDialog");
  KWindowConfig::saveWindowSize( windowHandle(), cg );
}

Polka::Identity NewGroupDialog::identity()
{
  if ( !m_matchList || m_matchList->selectionModel()->selectedIndexes().isEmpty() ) {
    Polka::Identity identity;
    identity.setType( "group" );
    Polka::Name name;
    name.setValue( m_nameInput->text() );
    identity.setName( name );
    return identity;
  } else {
    QModelIndexList selectedIndexes =
      m_matchList->selectionModel()->selectedIndexes();

    if ( selectedIndexes.count() > 1 ) {
      KMessageBox::information( 0, "More than one group selected" );
    }
    return m_model->findIdentity( m_proxyModel->data( selectedIndexes.first(),
      Qt::UserRole ).toString() );
  }
}

void NewGroupDialog::checkOkButton()
{
  m_okButton->setEnabled( !m_nameInput->text().isEmpty() );
}
