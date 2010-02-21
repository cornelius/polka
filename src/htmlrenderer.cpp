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

#include "htmlrenderer.h"

#include "htmlcreator.h"

#include <KLocale>

HtmlRenderer::HtmlRenderer()
{
}

QString HtmlRenderer::renderPerson( const Identity &identity )
{
  HtmlDoc doc;

  CssSheet css;

  CssRule &rule = css.rule( ".editbar" );

  rule.add( "background-color", "#80CCFF" );
  
  QString radius = "6px 6px";
  
  rule.add( "padding", radius );

  // FIXME: Make it work with more recent webkit version (seems to work in
  // Chromium, but not in QWebKit 4.5.
/*
  rule.add( "border-bottom-left-radius", radius );
  rule.add( "border-bottom-right-radius", radius );
  rule.add( "border-top-left-radius", radius );
  rule.add( "border-top-right-radius", radius );
*/

  rule.add( "-webkit-border-radius", "6px" );

  // Show edit link on hover
  css.addRule( ".edit-link", "font-size", "60%" );
  css.addRule( ".trigger span.edit-link", "display", "none" );
  css.addRule( ".trigger:hover span.edit-link", "display", "block" );

  doc.setCss( css );

  doc.element("h1").text(identity.displayName());
  if ( !identity.name().text().isEmpty() ) {
    doc.element("p").text(identity.name().text());
  }

  HtmlElement &div = doc.element("div");
//  div.attribute("contentEditable", true);
  foreach( Email email, identity.emails().emailList() ) {
    HtmlElement &a = div.element("div").element("a");
    a.attribute("href","mailto:" + email.text());
    a.text(email.text());
  }

  HtmlElement &commentsDiv = doc.element("div");
  commentsDiv.element("h2").text(i18n("Comments"));
  
  foreach( Comment comment, identity.comments().commentList() ) {
    HtmlElement &commentDiv = commentsDiv.element( "div" );
    commentDiv.attribute( "class", "trigger" );

    commentDiv.element("p").text( comment.text() );

    HtmlElement &span = commentDiv.element("span");
    span.attribute("class","edit-link");
    
    HtmlElement &a = span.element("a");
    a.attribute("href","polka:editComment/" + comment.id() );
    a.text("Edit");
  }

  HtmlElement &editBar = doc.element("div");
  editBar.attribute( "class", "editbar" );

  HtmlElement &addEmail = editBar.element("span").element("a");
  addEmail.attribute("href","polka:addEmail");
  addEmail.text("Add email");

  HtmlElement &addComment = editBar.element("span").element("a");
  addComment.attribute("href","polka:addComment");
  addComment.text("Add comment");

  return doc.html();
}
