= Polka

== Post 1.0

* GroupGraphicsView: Rename m_items to m_identityItems

* Retrieve gravatars
* Retrieve RoboHashes
* Fetch remote pictures
* Show progress when loading picture
* Show picture in addpicturewidget, if there already is one
* Provide a way to refresh pictures (automatically reload when addwidget is
  shown?)

* Menu handler for showing menus on top all the time.
* Move menu and tracking view code to lib.

* Rename ImageLoader to CloudHandler?

* Back button on canvas, top-left-corner, hide when no back

* Cloud connect

* Editing of group names (maybe use special personviewer?)

* Make PolkaView::insert protected and only use add and update?
* Don't show root group in group selector.

* Show nice text for links.
* Make sure new items don't overlap with existing moved ones.

* Handle geo location (locations/location/label|x|y)
* Undo based on git (Rollback from UI)
* Provide a way to get back to old images
* Canvas-based details view
* Zoom
* Multi-person picture importer (e.g. from group photo)
* Drop images e.g. from web pages to add new pictures to person
* Small pictures of people as group picture

* Clean up git debug output.
* Handle git errors
* Check for response when pulling from remote and don't reread data, if nothing
  has changed
* On first start ask, if to create a new data repo or use an existing (possibly
  remote) one
* Only pull and push, if repo actually has a remote repo configured
* Prevent saving while save is still in progress (especially with push)

* More than one (remote) repo, to separate for example private and job data. It
  could also be interesting to connect to your friends repos in some way.

* Migrate data between schema versions

* Explode sub group
* Create sub group from checked identities

* Group specific display names


= kxml_compiler

* Initialize integers in model classes.
* Move to stream reader, check that email addresses containing <jd>
work.
* eliminate pictures() from identity().pictures().pictureList()
* add a way to add custom functions to classes
  (e.g. bool isEmpty() { m_id.isEmpty(); })
* Recognize bool attributes (position.moved)
* Instead of List create pluralized forms.
* Support enums
