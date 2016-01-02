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

#include "phoneeditor.h"

#include <KLocalizedString>
#include <KConfigGroup>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

PhoneEditor::PhoneEditor( QWidget *parent )
  : QDialog( parent )
{
  setWindowTitle( i18n("Add phone number") );

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

  m_numberEdit = new QLineEdit;

  mainLayout->addWidget(m_numberEdit);
  mainLayout->addWidget(buttonBox);

  m_numberEdit->setFocus();
}

void PhoneEditor::setPhone( const Polka::Phone &phone )
{
  m_phone = phone;

  setWindowTitle( i18n("Edit phone number") );

  m_numberEdit->setText( phone.phoneNumber() );
}

Polka::Phone PhoneEditor::phone()
{
  m_phone.setPhoneNumber( m_numberEdit->text() );

  return m_phone;
}
