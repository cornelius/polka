// This file is generated by kxml_compiler from polka.xml.
// All changes you do to this file will be lost.
/*
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
#ifndef POLKA_POLKA_H
#define POLKA_POLKA_H

#include <polka/polka_export.h>
#include <QString>
#include <QDomElement>
#include <QList>
#include <QDate>

namespace Polka {

class POLKA_EXPORT ViewLabel
{
  public:
    typedef QList<ViewLabel> List;

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setText( const QString &v );
    QString text() const;
    void setX( int v );
    int x() const;
    void setY( int v );
    int y() const;
    /**
      Parse XML object from DOM element.
     */
    static ViewLabel parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mText;
    int mX;
    int mY;
};

class POLKA_EXPORT IdentityCheck
{
  public:
    typedef QList<IdentityCheck> List;

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setChecked( const QString &v );
    QString checked() const;
    /**
      Parse XML object from DOM element.
     */
    static IdentityCheck parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mChecked;
};

class POLKA_EXPORT IdentityPosition
{
  public:
    typedef QList<IdentityPosition> List;

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setX( int v );
    int x() const;
    void setY( int v );
    int y() const;
    /**
      Parse XML object from DOM element.
     */
    static IdentityPosition parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    int mX;
    int mY;
};

class POLKA_EXPORT GroupView
{
  public:
    typedef QList<GroupView> List;

  public:
    enum Flags { None, AutoCreate };

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void addIdentityPosition( const IdentityPosition &v );
    void setIdentityPositionList( const IdentityPosition::List &v );
    IdentityPosition::List identityPositionList() const;
    IdentityPosition findIdentityPosition( const QString &id, Flags flags = None );
    bool insert( const IdentityPosition &v );
    bool remove( const IdentityPosition &v );
    void addIdentityCheck( const IdentityCheck &v );
    void setIdentityCheckList( const IdentityCheck::List &v );
    IdentityCheck::List identityCheckList() const;
    IdentityCheck findIdentityCheck( const QString &id, Flags flags = None );
    bool insert( const IdentityCheck &v );
    bool remove( const IdentityCheck &v );
    void addViewLabel( const ViewLabel &v );
    void setViewLabelList( const ViewLabel::List &v );
    ViewLabel::List viewLabelList() const;
    ViewLabel findViewLabel( const QString &id, Flags flags = None );
    bool insert( const ViewLabel &v );
    bool remove( const ViewLabel &v );
    /**
      Parse XML object from DOM element.
     */
    static GroupView parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    IdentityPosition::List mIdentityPositionList;
    IdentityCheck::List mIdentityCheckList;
    ViewLabel::List mViewLabelList;
};

class POLKA_EXPORT Comment
{
  public:
    typedef QList<Comment> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setText( const QString &v );
    QString text() const;
    /**
      Parse XML object from DOM element.
     */
    static Comment parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mUpdatedAt;
    QString mText;
};

class POLKA_EXPORT Comments
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addComment( const Comment &v );
    void setCommentList( const Comment::List &v );
    Comment::List commentList() const;
    Comment findComment( const QString &id, Flags flags = None );
    bool insert( const Comment &v );
    bool remove( const Comment &v );
    /**
      Parse XML object from DOM element.
     */
    static Comments parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Comment::List mCommentList;
};

class POLKA_EXPORT Attribute
{
  public:
    typedef QList<Attribute> List;

  public:
    void setType( const QString &v );
    QString type() const;
    void setKey( const QString &v );
    QString key() const;
    void setValue( const QString &v );
    QString value() const;
    /**
      Parse XML object from DOM element.
     */
    static Attribute parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mType;
    QString mKey;
    QString mValue;
};

class POLKA_EXPORT ExtendedAttributes
{
  public:
    void addAttribute( const Attribute &v );
    void setAttributeList( const Attribute::List &v );
    Attribute::List attributeList() const;
    /**
      Parse XML object from DOM element.
     */
    static ExtendedAttributes parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Attribute::List mAttributeList;
};

class POLKA_EXPORT Link
{
  public:
    typedef QList<Link> List;

  public:
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setLinkType( const QString &v );
    QString linkType() const;
    void setUrl( const QString &v );
    QString url() const;
    /**
      Parse XML object from DOM element.
     */
    static Link parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mUpdatedAt;
    QString mId;
    QString mLinkType;
    QString mUrl;
};

class POLKA_EXPORT Links
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addLink( const Link &v );
    void setLinkList( const Link::List &v );
    Link::List linkList() const;
    Link findLink( const QString &id, Flags flags = None );
    bool insert( const Link &v );
    bool remove( const Link &v );
    /**
      Parse XML object from DOM element.
     */
    static Links parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Link::List mLinkList;
};

class POLKA_EXPORT Note
{
  public:
    typedef QList<Note> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setCreatedAt( const QString &v );
    QString createdAt() const;
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setText( const QString &v );
    QString text() const;
    /**
      Parse XML object from DOM element.
     */
    static Note parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mCreatedAt;
    QString mUpdatedAt;
    QString mText;
};

class POLKA_EXPORT Notes
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addNote( const Note &v );
    void setNoteList( const Note::List &v );
    Note::List noteList() const;
    Note findNote( const QString &id, Flags flags = None );
    bool insert( const Note &v );
    bool remove( const Note &v );
    /**
      Parse XML object from DOM element.
     */
    static Notes parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Note::List mNoteList;
};

class POLKA_EXPORT Relation
{
  public:
    typedef QList<Relation> List;

  public:
    void setRelationType( const QString &v );
    QString relationType() const;
    void setTarget( const QString &v );
    QString target() const;
    /**
      Parse XML object from DOM element.
     */
    static Relation parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mRelationType;
    QString mTarget;
};

class POLKA_EXPORT Relations
{
  public:
    void addRelation( const Relation &v );
    void setRelationList( const Relation::List &v );
    Relation::List relationList() const;
    /**
      Parse XML object from DOM element.
     */
    static Relations parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Relation::List mRelationList;
};

class POLKA_EXPORT Address
{
  public:
    typedef QList<Address> List;

  public:
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setLabel( const QString &v );
    QString label() const;
    /**
      Parse XML object from DOM element.
     */
    static Address parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mUpdatedAt;
    QString mId;
    QString mLabel;
};

class POLKA_EXPORT Addresses
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addAddress( const Address &v );
    void setAddressList( const Address::List &v );
    Address::List addressList() const;
    Address findAddress( const QString &id, Flags flags = None );
    bool insert( const Address &v );
    bool remove( const Address &v );
    /**
      Parse XML object from DOM element.
     */
    static Addresses parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Address::List mAddressList;
};

class POLKA_EXPORT Phone
{
  public:
    typedef QList<Phone> List;

  public:
    void setComment( const QString &v );
    QString comment() const;
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setPhoneType( const QString &v );
    QString phoneType() const;
    void setPhoneNumber( const QString &v );
    QString phoneNumber() const;
    /**
      Parse XML object from DOM element.
     */
    static Phone parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mComment;
    QString mUpdatedAt;
    QString mId;
    QString mPhoneType;
    QString mPhoneNumber;
};

class POLKA_EXPORT Phones
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addPhone( const Phone &v );
    void setPhoneList( const Phone::List &v );
    Phone::List phoneList() const;
    Phone findPhone( const QString &id, Flags flags = None );
    bool insert( const Phone &v );
    bool remove( const Phone &v );
    /**
      Parse XML object from DOM element.
     */
    static Phones parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Phone::List mPhoneList;
};

class POLKA_EXPORT Picture
{
  public:
    typedef QList<Picture> List;

  public:
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setPictureType( const QString &v );
    QString pictureType() const;
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setUrl( const QString &v );
    QString url() const;
    /**
      Parse XML object from DOM element.
     */
    static Picture parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mUpdatedAt;
    QString mPictureType;
    QString mId;
    QString mUrl;
};

class POLKA_EXPORT Pictures
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addPicture( const Picture &v );
    void setPictureList( const Picture::List &v );
    Picture::List pictureList() const;
    Picture findPicture( const QString &id, Flags flags = None );
    bool insert( const Picture &v );
    bool remove( const Picture &v );
    /**
      Parse XML object from DOM element.
     */
    static Pictures parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Picture::List mPictureList;
};

class POLKA_EXPORT Email
{
  public:
    typedef QList<Email> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setText( const QString &v );
    QString text() const;
    /**
      Parse XML object from DOM element.
     */
    static Email parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mUpdatedAt;
    QString mText;
};

class POLKA_EXPORT Emails
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addEmail( const Email &v );
    void setEmailList( const Email::List &v );
    Email::List emailList() const;
    Email findEmail( const QString &id, Flags flags = None );
    bool insert( const Email &v );
    bool remove( const Email &v );
    /**
      Parse XML object from DOM element.
     */
    static Emails parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Email::List mEmailList;
};

class POLKA_EXPORT Group
{
  public:
    typedef QList<Group> List;

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    /**
      Parse XML object from DOM element.
     */
    static Group parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
};

class POLKA_EXPORT Groups
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void addGroup( const Group &v );
    void setGroupList( const Group::List &v );
    Group::List groupList() const;
    Group findGroup( const QString &id, Flags flags = None );
    bool insert( const Group &v );
    bool remove( const Group &v );
    /**
      Parse XML object from DOM element.
     */
    static Groups parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Group::List mGroupList;
};

class POLKA_EXPORT Name
{
  public:
    void setUpdatedAt( const QString &v );
    QString updatedAt() const;
    void setText( const QString &v );
    QString text() const;
    /**
      Parse XML object from DOM element.
     */
    static Name parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mUpdatedAt;
    QString mText;
};

class POLKA_EXPORT Identity
{
  public:
    typedef QList<Identity> List;

  public:
    void setId( const QString &v );
    QString id() const;
    bool isValid() const;
    void setGroups( const Groups &v );
    Groups groups() const;
    void setName( const Name &v );
    Name name() const;
    void setBirthname( const QString &v );
    QString birthname() const;
    void setBirthday( const QDate &v );
    QDate birthday() const;
    void setEmails( const Emails &v );
    Emails emails() const;
    void setPictures( const Pictures &v );
    Pictures pictures() const;
    void setPhones( const Phones &v );
    Phones phones() const;
    void setAddresses( const Addresses &v );
    Addresses addresses() const;
    void setRelations( const Relations &v );
    Relations relations() const;
    void setNotes( const Notes &v );
    Notes notes() const;
    void setLinks( const Links &v );
    Links links() const;
    void setExtendedAttributes( const ExtendedAttributes &v );
    ExtendedAttributes extendedAttributes() const;
    void setComments( const Comments &v );
    Comments comments() const;
    /**
      Parse XML object from DOM element.
     */
    static Identity parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    Groups mGroups;
    Name mName;
    QString mBirthname;
    QDate mBirthday;
    Emails mEmails;
    Pictures mPictures;
    Phones mPhones;
    Addresses mAddresses;
    Relations mRelations;
    Notes mNotes;
    Links mLinks;
    ExtendedAttributes mExtendedAttributes;
    Comments mComments;
};

class POLKA_EXPORT Polka
{
  public:
    enum Flags { None, AutoCreate };

  public:
    void setSchemaVersion( const QString &v );
    QString schemaVersion() const;
    void addIdentity( const Identity &v );
    void setIdentityList( const Identity::List &v );
    Identity::List identityList() const;
    Identity findIdentity( const QString &id, Flags flags = None );
    bool insert( const Identity &v );
    bool remove( const Identity &v );
    void addGroupView( const GroupView &v );
    void setGroupViewList( const GroupView::List &v );
    GroupView::List groupViewList() const;
    GroupView findGroupView( const QString &id, Flags flags = None );
    bool insert( const GroupView &v );
    bool remove( const GroupView &v );
    /**
      Parse XML object from DOM element.
     */
    static Polka parseElement( const QDomElement &element, bool *ok );
    QString writeElement();
    static Polka parseFile( const QString &filename, bool *ok );
    bool writeFile( const QString &filename );

  private:
    QString mSchemaVersion;
    Identity::List mIdentityList;
    GroupView::List mGroupViewList;
};

}

#endif
