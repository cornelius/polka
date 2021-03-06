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

#include "polkamodel.h"

#include "gitdir.h"
#include "gitremote.h"
#include "settings.h"
#include "polkaallitemmodel.h"
#include "polkapersonsitemmodel.h"
#include "imageloader.h"
#include "firststartdata.h"

#include <KRandom>
#include <KLocalizedString>

#include <QStandardPaths>
#include <QDir>
#include <QDebug>

PolkaModel::PolkaModel( QObject *parent )
  : QObject( parent ), m_writesEnabled( true ),
    m_allItemModel( 0 ), m_personsItemModel( 0 ),
    m_groupItemModel( 0 )
{
  m_defaultGroupPixmapPath = QStandardPaths::locate( QStandardPaths::DataLocation,
    "polka_group.png" );
  m_defaultGroupPixmap = QPixmap( m_defaultGroupPixmapPath );
  m_defaultPersonPixmapPath = QStandardPaths::locate( QStandardPaths::DataLocation,
    "polka_person.png" );
  m_defaultPersonPixmap = QPixmap( m_defaultPersonPixmapPath );

  m_gitDir = new GitDir( QDir::homePath() + "/.polka" );

  m_gitRemote = new GitRemote( m_gitDir );
  connect( m_gitRemote, SIGNAL( pulled() ), SLOT( readData() ) );
  connect( m_gitRemote, SIGNAL( pushed() ), SLOT( slotPushed() ) );

  connect( m_gitDir, SIGNAL( commandExecuted( const GitCommand & ) ),
    SLOT( slotCommandExecuted( const GitCommand & ) ) );
}

PolkaModel::~PolkaModel()
{
  delete m_gitDir;
}

GitRemote *PolkaModel::gitRemote() const
{
  return m_gitRemote;
}

GitDir *PolkaModel::gitDir() const
{
  return m_gitDir;
}

Polka::Identity PolkaModel::findIdentity( const QString &id )
{
  return m_polka.findIdentity( id );
}

Polka::Identity::List PolkaModel::allIdentities()
{
  return m_polka.identityList();
}

Polka::Identity PolkaModel::rootGroup()
{
  return m_rootGroup;
}

Polka::Identity::List PolkaModel::groups()
{
  return m_groups;
}

Polka::Identity::List PolkaModel::persons()
{
  // FIXME: Cache it in model.

  Polka::Identity::List persons;

  foreach( Polka::Identity identity, m_polka.identityList() ) {
    if ( identity.type() != "group" ) {
      persons.append( identity );
    }
  }

  return persons;
}

Polka::Identity::List PolkaModel::identitiesOfGroup( const Polka::Identity &group )
{
  return identitiesOfGroup( group.id() );
}

Polka::Identity::List PolkaModel::identitiesOfGroup( const QString &id )
{
  if ( id.isEmpty() ) return m_groups;
  if ( !m_groupMap.contains( id ) ) {
    m_groupMap.insert( id, Polka::Identity::List() );
  }
  return m_groupMap[ id ];
}

PolkaItemModel *PolkaModel::allItemModel()
{
  if ( !m_allItemModel ) {
    m_allItemModel = new PolkaAllItemModel( this );
  }
  return m_allItemModel;
}

PolkaItemModel *PolkaModel::personsItemModel()
{
  if ( !m_personsItemModel ) {
    m_personsItemModel = new PolkaPersonsItemModel( this );
  }
  return m_personsItemModel;
}

PolkaItemModel *PolkaModel::itemModel( const QString &id )
{
  if ( !m_itemModels.contains( id ) ) {
    PolkaItemModel *itemModel = new PolkaItemModel( this, id );
    m_itemModels.insert( id, itemModel );
  }
  return m_itemModels.value( id );
}

PolkaItemModel *PolkaModel::groupItemModel()
{
  if ( !m_groupItemModel ) {
    m_groupItemModel = new PolkaItemModel( this );
  }
  return m_groupItemModel;
}

bool PolkaModel::readData()
{
  QString dataFile = m_gitDir->filePath( "std.polka" );

  if ( QFile::exists( dataFile ) ) {
    m_polka = Polka::Polka::parseFile( dataFile, &m_dataIsValid );

    if ( !m_dataIsValid ) {
      return false;
    }
  } else {
    m_dataIsValid = true;
  }

  foreach( Polka::Identity identity, m_polka.identityList() ) {
    if ( identity.id().isEmpty() ) {
      identity.setId( KRandom::randomString( 10 ) );
      m_polka.insert( identity );
    }
  }

  Polka::Group rootGroup = m_polka.root().group();

  m_rootGroup = m_polka.findIdentity( rootGroup.id() );
  if ( !m_rootGroup.isValid() ) {
    m_rootGroup.setId( KRandom::randomString( 10 ) );

    m_rootGroup.setType( "group" );
    Polka::Name n;
    n.setValue( i18n("Your people") );
    m_rootGroup.setName( n );

    m_polka.insert( m_rootGroup );

    Polka::Root root;
    rootGroup.setId( m_rootGroup.id() );
    root.setGroup( rootGroup );
    m_polka.setRoot( root );
  }

  setupGroups();

  if ( !QFile::exists( dataFile ) ) {
    FirstStartData data( this );
    data.create();
  }

  return true;
}

void PolkaModel::setupGroups()
{
  m_groups.clear();
  m_groupMap.clear();

  foreach( Polka::Identity identity, m_polka.identityList() ) {
    if ( identity.groups().groupList().isEmpty() &&
         identity.type() != "group" ) {
      identity.setType( "group" );
      m_polka.insert( identity );
    }

    if ( identity.type() == "group" ) {
      m_groups.append( identity );
    }

    foreach( Polka::Group group, identity.groups().groupList() ) {
      if ( m_groupMap.contains( group.id() ) ) {
        m_groupMap[ group.id() ].append( identity );
      } else {
        Polka::Identity::List identityList;
        identityList.append( identity );
        m_groupMap.insert( group.id(), identityList );
      }
    }
  }
}

void PolkaModel::setWritesEnabled( bool enabled )
{
  m_writesEnabled = enabled;
}

void PolkaModel::writeData( const QString &msg )
{
  if ( !m_writesEnabled ) {
    return;
  }

  if ( !m_dataIsValid) {
    emit dataWritten();
    return;
  }

  // FIXME: If writeData is called multiple times in short sequence, especially
  // if done from code, it it likely that the git command hasn't run yet, and
  // data is not committed then. It is committed on exit of the application.
  // To properly fix this, the writing of the data would have to be queued
  // together with the commit.
  // It might be easier to just eliminate subsequent commits from code, assuming
  // that user interactions are never faster than git.
  if ( !m_commitCommands.isEmpty() ) {
    qDebug() << "WARNING: Commit still running, not committing:" << msg;
    return;
  }

  m_polka.writeFile( m_gitDir->filePath( "std.polka" ) );
  m_gitDir->addFile( "std.polka", msg );
  m_commitCommands.append(
    m_gitDir->commitData( i18n("Saving pending changes") ) );
}

void PolkaModel::slotCommandExecuted( const GitCommand &cmd )
{
  m_commitCommands.removeOne( cmd.id() );
  if ( m_commitCommands.isEmpty() ) {
    if ( !Settings::remoteSyncingEnabled() ) {
      emit dataWritten();
    }
  }
}

void PolkaModel::slotPushed()
{
  emit dataWritten();
}

Polka::Identity PolkaModel::insert( Polka::Identity identity,
  const QString &msg )
{
  bool added;

  if ( identity.id().isEmpty() ) {
    identity.setId( KRandom::randomString( 10 ) );
    added = true;
  } else {
    if ( m_polka.findIdentity( identity.id() ).isValid() ) {
      added = false;
    } else {
      added = true;
    }
  }

  m_polka.insert( identity );

  setupGroups();

  if ( identity.type() == "group" ) {
    groupItemModel()->updateData();
  }

  foreach( Polka::Group group, identity.groups().groupList() ) {
    itemModel( group.id() )->updateData();
  }

  writeData( msg );

  if ( added ) emit identityAdded( identity );
  else emit identityChanged( identity );

  return identity;
}

Polka::Identity PolkaModel::addIdentity( const Polka::Identity &person,
  const Polka::Identity &group )
{
  Polka::Identity p = person;

  Polka::Groups groups = p.groups();

  if ( !groups.findGroup( group.id() ).isValid() ) {
    Polka::Group g;
    g.setId( group.id() );
    groups.addGroup( g );
    p.setGroups( groups );

    return insert( p, i18n("Add %1 to group %2").arg( person.name().value() )
      .arg( group.name().value() ) );
  }

  return Polka::Identity();
}

void PolkaModel::removeIdentity( const Polka::Identity &identity,
  const Polka::Identity &group )
{
  Polka::Group::List groups = identity.groups().groupList();
  Polka::Group::List newGroups;

  foreach( Polka::Group g, groups ) {
    if ( g.id() != group.id() ) {
      newGroups.append( g );
    }
  }

  if ( identity.type() != "group" && newGroups.isEmpty() ) {
    m_polka.remove( identity );

    setupGroups();

    writeData( i18n("Deleted %1").arg( identity.name().value() ) );

    emit identityRemoved( identity );
  } else {
    Polka::Identity newIdentity = identity;

    Polka::Groups gg;
    gg.setGroupList( newGroups );
    newIdentity.setGroups( gg );
    m_polka.insert( newIdentity );

    setupGroups();

    writeData( i18n("Removed %1 from group %2")
      .arg( newIdentity.name().value() )
      .arg( group.name().value() ) );

    emit identityChanged( newIdentity );
  }
}

void PolkaModel::removeGroup( const Polka::Identity &group )
{
  Polka::Identity::List members = m_groupMap.value( group.id() );
  foreach( Polka::Identity member, members ) {
    removeIdentity( member, group );
  }
  m_polka.remove( group );
  m_polka.remove( m_polka.findGroupView( group.id() ) );

  setupGroups();

  emit identityRemoved( group );
}

QPixmap PolkaModel::pixmap( const Polka::Picture &picture ) const
{
  LocalPicture *local = localPicture( picture );

  if ( !local ) return m_defaultPersonPixmap;

  return local->pixmap();
}

QPixmap PolkaModel::pixmap( const Polka::Identity &identity ) const
{
  Polka::Pictures pictures = identity.pictures();

  if ( pictures.pictureList().isEmpty() ) return defaultPixmap( identity );

  Polka::Picture selectedPicture = pictures.findPicture(
    pictures.selected() );
  if ( !selectedPicture.isValid() ) {
    selectedPicture = pictures.pictureList().first();
  }

  LocalPicture *local = localPicture( selectedPicture );

  if ( !local ) return defaultPixmap( identity );

  return local->pixmap();
}

QString PolkaModel::pixmapPath( const Polka::Identity &identity ) const
{
  Polka::Pictures pictures = identity.pictures();

  if ( pictures.pictureList().isEmpty() ) return defaultPixmapPath( identity );

  Polka::Picture selectedPicture = pictures.findPicture(
    pictures.selected() );
  if ( !selectedPicture.isValid() ) {
    selectedPicture = pictures.pictureList().first();
  }

  LocalPicture *local = localPicture( selectedPicture );

  if ( !local ) return defaultPixmapPath( identity );

  return local->fullFilePath();
}

QPixmap PolkaModel::defaultPixmap( const Polka::Identity &identity ) const
{
  if ( identity.type() == "group" ) return m_defaultGroupPixmap;
  else return m_defaultPersonPixmap;
}

QString PolkaModel::defaultPixmapPath( const Polka::Identity &identity ) const
{
  if ( identity.type() == "group" ) return m_defaultGroupPixmapPath;
  else return m_defaultPersonPixmapPath;
}

LocalPicture *PolkaModel::localPicture( const Polka::Picture &picture ) const
{
  if ( m_localPictures.contains( picture.id() ) ) {
    return m_localPictures.value( picture.id() );
  }

  LocalPicture *localPicture = new LocalPicture( m_gitDir, picture );

  m_localPictures.insert( picture.id(), localPicture );

  return localPicture;
}

void PolkaModel::insertPicture( ImageLoader *loader )
{
  doInsertPicture( loader->pixmap(), loader->picture(), loader->identity() );

  Polka::Identity identity = findIdentity( loader->identity().id() );

  Polka::Link link;
  link.setId( KRandom::randomString( 10 ) );

  Polka::Links links = identity.links();

  foreach( Polka::Link l, links.linkList() ) {
    if ( l.linkType() == loader->picture().pictureType() ) {
      link = l;
      break;
    }
  }

  link.setLinkType( loader->picture().pictureType() );
  link.setUsername( loader->username() );
  link.setUrl( loader->profileUrl().url() );

  links.insert( link );
  identity.setLinks( links );

  m_polka.insert( identity );

  writeData( i18n("Added picture of %1").arg( identity.name().value() ) );

  emit identityChanged( identity );
}

void PolkaModel::insertPicture( const QPixmap &pixmap,
                                const Polka::Picture &picture,
                                const Polka::Identity &identity )
{
  doInsertPicture( pixmap, picture, identity );

  writeData( i18n("Added picture of %1").arg( identity.name().value() ) );

  emit identityChanged( m_polka.findIdentity( identity.id() ) );
}

void PolkaModel::doInsertPicture( const QPixmap &pixmap,
  const Polka::Picture &picture, const Polka::Identity &target )
{
  Polka::Identity identity = findIdentity( target.id() );

  Polka::Pictures pictures = identity.pictures();
  Polka::Picture::List pictureList = pictures.pictureList();

  LocalPicture *localPicture = new LocalPicture( m_gitDir, picture );
  localPicture->setPixmap( pixmap, identity );

  pictureList.append( picture );
  pictures.setPictureList( pictureList );
  identity.setPictures( pictures );
  m_polka.insert( identity );

  m_localPictures.insert( picture.id(), localPicture );
}

void PolkaModel::setDefaultPicture( const Polka::Picture &picture,
  Polka::Identity &identity )
{
  Polka::Pictures pictures = identity.pictures();
  pictures.setSelected( picture.id() );
  identity.setPictures( pictures );
  m_polka.insert( identity );

  emit identityChanged( identity );
}

void PolkaModel::removePicture( const Polka::Picture &picture,
  Polka::Identity &identity )
{
  Polka::Pictures pictures = identity.pictures();
  pictures.remove( picture );

  identity.setPictures( pictures );

  m_polka.insert( identity );

  writeData( i18n("Removed picture of %1").arg( identity.name().value() ) );

  emit identityChanged( identity );
}

void PolkaModel::saveViewLabel( const Polka::Identity &group,
  const Polka::ViewLabel &label )
{
  Polka::GroupView v = m_polka.findGroupView( group.id(),
    Polka::Polka::AutoCreate );
  v.insert( label );
  m_polka.insert( v );
  writeData( i18n("Inserted label %1").arg( label.text() ) );
}

void PolkaModel::removeViewLabel( const Polka::Identity &group,
  const Polka::ViewLabel &label )
{
  QString labelText = label.text();

  Polka::GroupView v = m_polka.findGroupView( group.id(),
    Polka::Polka::AutoCreate );
  v.remove( label );
  m_polka.insert( v );
  writeData( i18n("Removed label %1").arg( labelText ) );
}

void PolkaModel::saveViewPosition( const Polka::Identity &group,
  const Polka::Identity &identity,
  const QPointF &pos )
{
  Polka::GroupView v = m_polka.findGroupView( group.id(),
    Polka::Polka::AutoCreate );
  Polka::IdentityPosition p = v.findIdentityPosition( identity.id(),
    Polka::GroupView::AutoCreate );
  p.setX( pos.x() );
  p.setY( pos.y() );
  v.insert( p );
  m_polka.insert( v );
  writeData( i18n("Moved %1 in group %2")
    .arg( identity.name().value() ).arg( group.name().value() ) );
}

void PolkaModel::clearViewPositions( const Polka::Identity &group )
{
  Polka::GroupView view = m_polka.findGroupView( group.id() );
  view.setIdentityPositionList( Polka::IdentityPosition::List() );
  m_polka.insert( view );
  writeData( i18n("Reset positions in group %1").arg( group.name().value() ) );
}

void PolkaModel::saveViewCheck( const Polka::Identity &group,
  const Polka::Identity &identity,
  bool checked )
{
  QString msg;

  Polka::GroupView v = m_polka.findGroupView( group.id(),
    Polka::Polka::AutoCreate );
  if ( checked ) {
    Polka::IdentityCheck c = v.findIdentityCheck( identity.id(),
      Polka::GroupView::AutoCreate );
    v.insert( c );
    msg = i18n("Checked %1").arg( identity.name().value() );
  } else {
    Polka::IdentityCheck c = v.findIdentityCheck( identity.id(),
      Polka::GroupView::AutoCreate );
    if ( c.isValid() ) v.remove( c );
    msg = i18n("Unchecked %1").arg( identity.name().value() );
  }
  m_polka.insert( v );
  writeData( msg );
}

Polka::GroupView PolkaModel::groupView( const Polka::Identity &group )
{
  return m_polka.findGroupView( group.id() );
}

Polka::Link PolkaModel::link( const Polka::Identity &identity,
  const QString &linkType ) const
{
  foreach( Polka::Link link, identity.links().linkList() ) {
    if ( link.linkType() == linkType ) return link;
  }
  return Polka::Link();
}
