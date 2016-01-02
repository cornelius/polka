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

#include "addresseditor.h"

#include <KLocalizedString>
#include <KConfigGroup>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

AddressEditor::AddressEditor( QWidget *parent )
  : QDialog( parent )
{
  setWindowTitle( i18n("Add address") );

  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  QWidget *mainWidget = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
  mainLayout->addWidget(mainWidget);

  QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
  okButton->setDefault(true);
  okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  setModal( true );

  m_edit = new QTextEdit;

  mainLayout->addWidget( m_edit );
  mainLayout->addWidget(buttonBox);

  m_edit->setFocus();
}

void AddressEditor::setAddress( const QString &text )
{
  setWindowTitle( i18n("Edit address") );

  m_edit->setPlainText( text );
}

QString AddressEditor::address() const
{
  return m_edit->toPlainText();
}
