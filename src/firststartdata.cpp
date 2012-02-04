/*
    This file is part of KDE.

    Copyright (c) 2012 Cornelius Schumacher <schumacher@kde.org>

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

#include "firststartdata.h"

#include <KLocale>
#include <KRandom>

FirstStartData::FirstStartData( PolkaModel *model )
  : m_model( model )
{
}

void FirstStartData::create()
{
  Polka::Identity me;
  Polka::Name name = me.name();
  name.setValue( "Cornelius Schumacher" );
  me.setName( name );
  me = m_model->addIdentity( me, m_model->rootGroup() );
  
  Polka::Email email;
  email.setEmailAddress( "schumacher@kde.org" );
  Polka::Emails emails;
  emails.addEmail( email );
  me.setEmails( emails );

  Polka::Comment comment;
  comment.setValue( i18n("I'm Cornelius Schumacher, the author of Polka, "
    "the humane address book for the cloud. "
    "If you have feedback or questions, or you would like to help, "
    "please don't hesitate to contact me. Have fun with Polka.") );  
  Polka::Comments comments;
  comments.addComment( comment );
  me.setComments( comments );
  
  m_model->insert( me, i18n("Welcome to Polka") );

  m_model->saveViewPosition( m_model->rootGroup(), me, QPointF( 0, 0 ) );

  QString txt;
  
  txt = i18n("Welcome to Polka!\n\n"
    "The goal of Polka is to provide a humane way\n"
    "for managing your information about other people,\n"
    "using natural concepts like groups, pictures,\n"
    "history, annotations, ubiquitous access.\n\n"
    "It hooks into the cloud, and aims at providing\n"
    "a dynamic and elegant user interface.\n\n"
    "This is an early preview. Feedback is welcome.\n\n"
    "For some help with the UI, go to the Help group.\n\n"
    "Have fun with Polka." );
  createLabel( m_model->rootGroup(), txt, 274, -142 );

  Polka::Identity helpGroup;
  name.setValue( i18n("Help") );
  helpGroup.setName( name );
  helpGroup.setType( "group" );
  
  helpGroup = m_model->addIdentity( helpGroup, m_model->rootGroup() );

  m_model->saveViewPosition( m_model->rootGroup(), helpGroup,
    QPointF( -200, -300 ) );

  txt = i18n("Hover or touch the menu at the top right for\n"
    "some general actions.");
  createLabel( helpGroup, txt, 160, -200 );

  txt = i18n("Drag label at the side to the canvas\n"
    "to create a new label.");
  createLabel( helpGroup, txt, 250, -100 );

  txt = i18n("Click the plus icon at the bottom left to open the"
    "group target.\n"
    "Drop people or groups on the target to add them\n"
    "to the selected group. Use arrows to select the target group." );
  createLabel( helpGroup, txt, -100, 150 );

  txt = i18n("Click the left arrow button outside of the view\n"
    "to get back to the previous group." );
  createLabel( helpGroup, txt, -300, -250 );
}

void FirstStartData::createLabel( const Polka::Identity &group,
  const QString &text, int x, int y )
{
  Polka::ViewLabel label;
  label.setId( KRandom::randomString( 10 ) );
  label.setText( text );
  label.setX( x );
  label.setY( y );
  
  m_model->saveViewLabel( group, label );  
}
