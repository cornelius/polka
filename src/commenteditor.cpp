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

#include "commenteditor.h"

#include <KLocalizedString>
#include <KConfigGroup>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

CommentEditor::CommentEditor( QWidget *parent )
  : QDialog( parent )
{
  setWindowTitle( i18n("Add comment") );

  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  QWidget *mainWidget = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
  mainLayout->addWidget(mainWidget);
  QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
  okButton->setDefault(true);
  okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  QPushButton *user1Button = new QPushButton;
  buttonBox->addButton(user1Button, QDialogButtonBox::ActionRole);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  setModal( true );

  user1Button->setText(i18n("Clear" ));
  connect(user1Button, SIGNAL( clicked() ), SLOT( clearComment() ) );

  m_edit = new QTextEdit;

  mainLayout->addWidget(m_edit);
  mainLayout->addWidget(buttonBox);

  m_edit->setFocus();
}

void CommentEditor::setComment( const QString &text )
{
  setWindowTitle( i18n("Edit comment") );

  m_edit->setPlainText( text );
}

QString CommentEditor::comment() const
{
  return m_edit->toPlainText();
}

void CommentEditor::clearComment()
{
  m_edit->clear();
  m_edit->setFocus();
}
