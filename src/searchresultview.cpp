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

#include "searchresultview.h"

#include "matchlist.h"

#include <QBoxLayout>

SearchResultView::SearchResultView( PolkaModel *model )
  : m_model( model )
{
  QBoxLayout *topLayout = new QHBoxLayout( this );

  topLayout->addStretch( 1 );

  m_matchList = new MatchList( m_model );
  connect( m_matchList, SIGNAL( activated() ), SLOT( slotActivated() ) );
  topLayout->addWidget( m_matchList );

  topLayout->addStretch( 1 );
}

void SearchResultView::search( const QString &text )
{
  m_matchList->filter( text );
}

void SearchResultView::slotActivated()
{
  emit identityActivated( m_matchList->identity() );
}
