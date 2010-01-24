// This file is generated by kxml_compiler from polka.xml.
// All changes you do to this file will be lost.
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
#ifndef POLKA_H
#define POLKA_H

#include <QDomElement>
#include <QList>
#include <QString>
#include <QDate>

class Comment
{
  public:
    typedef QList<Comment> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setText( const QString &v );
    QString text() const;
    /**
      Parse XML object from DOM element.
     */
    static Comment parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    QString mText;
};

class Comments
{
  public:
    void addComment( const Comment &v );
    void setCommentList( const Comment::List &v );
    Comment::List commentList() const;
    /**
      Parse XML object from DOM element.
     */
    static Comments parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Comment::List mCommentList;
};

class Attribute
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

class ExtendedAttributes
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

class Profile
{
  public:
    typedef QList<Profile> List;

  public:
    void setProfileType( const QString &v );
    QString profileType() const;
    void setUrl( const QString &v );
    QString url() const;
    /**
      Parse XML object from DOM element.
     */
    static Profile parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mProfileType;
    QString mUrl;
};

class Profiles
{
  public:
    void addProfile( const Profile &v );
    void setProfileList( const Profile::List &v );
    Profile::List profileList() const;
    /**
      Parse XML object from DOM element.
     */
    static Profiles parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Profile::List mProfileList;
};

class Note
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

class Notes
{
  public:
    void addNote( const Note &v );
    void setNoteList( const Note::List &v );
    Note::List noteList() const;
    /**
      Parse XML object from DOM element.
     */
    static Notes parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Note::List mNoteList;
};

class Relation
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

class Relations
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

class Phone
{
  public:
    typedef QList<Phone> List;

  public:
    void setComment( const QString &v );
    QString comment() const;
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
    QString mPhoneType;
    QString mPhoneNumber;
};

class Phones
{
  public:
    void addPhone( const Phone &v );
    void setPhoneList( const Phone::List &v );
    Phone::List phoneList() const;
    /**
      Parse XML object from DOM element.
     */
    static Phones parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Phone::List mPhoneList;
};

class Picture
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

class Pictures
{
  public:
    void addPicture( const Picture &v );
    void setPictureList( const Picture::List &v );
    Picture::List pictureList() const;
    /**
      Parse XML object from DOM element.
     */
    static Pictures parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Picture::List mPictureList;
};

class Email
{
  public:
    typedef QList<Email> List;

  public:
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
    QString mUpdatedAt;
    QString mText;
};

class Emails
{
  public:
    void addEmail( const Email &v );
    void setEmailList( const Email::List &v );
    Email::List emailList() const;
    /**
      Parse XML object from DOM element.
     */
    static Emails parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Email::List mEmailList;
};

class Position
{
  public:
    void setMoved( const QString &v );
    QString moved() const;
    void setX( int v );
    int x() const;
    void setY( int v );
    int y() const;
    /**
      Parse XML object from DOM element.
     */
    static Position parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mMoved;
    int mX;
    int mY;
};

class Group
{
  public:
    typedef QList<Group> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setPosition( const Position &v );
    Position position() const;
    /**
      Parse XML object from DOM element.
     */
    static Group parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    QString mId;
    Position mPosition;
};

class Groups
{
  public:
    void addGroup( const Group &v );
    void setGroupList( const Group::List &v );
    Group::List groupList() const;
    /**
      Parse XML object from DOM element.
     */
    static Groups parseElement( const QDomElement &element, bool *ok );
    QString writeElement();

  private:
    Group::List mGroupList;
};

class Name
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

class Identity
{
  public:
    typedef QList<Identity> List;

  public:
    void setId( const QString &v );
    QString id() const;
    void setGroups( const Groups &v );
    Groups groups() const;
    void setDisplayName( const QString &v );
    QString displayName() const;
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
    void setRelations( const Relations &v );
    Relations relations() const;
    void setNotes( const Notes &v );
    Notes notes() const;
    void setProfiles( const Profiles &v );
    Profiles profiles() const;
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
    QString mDisplayName;
    Name mName;
    QString mBirthname;
    QDate mBirthday;
    Emails mEmails;
    Pictures mPictures;
    Phones mPhones;
    Relations mRelations;
    Notes mNotes;
    Profiles mProfiles;
    ExtendedAttributes mExtendedAttributes;
    Comments mComments;
};

class Polka
{
  public:
    void setSchemaVersion( const QString &v );
    QString schemaVersion() const;
    void addIdentity( const Identity &v );
    void setIdentityList( const Identity::List &v );
    Identity::List identityList() const;
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
};

#endif
