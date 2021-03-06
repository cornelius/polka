set(polka_bin_SRCS
  writetransaction.cpp
  firststartdata.cpp
  imageloaderfacebook.cpp
  imageloadertwitter.cpp
  addpicturewidget.cpp
  matchlist.cpp
  searchresultview.cpp
  searchedit.cpp
  fanmenuitem.cpp
  buttonitem.cpp
  groupadderitem.cpp
  historyview.cpp
  overview.cpp
  groupview.cpp
  pictureselectorcontrols.cpp
  roundedrectitem.cpp
  settingswidget.cpp
  magicmenuitem.cpp
  mainmenuitem.cpp
  newgroupdialog.cpp
  labelitem.cpp
  addresseditor.cpp
  linkeditor.cpp
  phoneeditor.cpp
  commenteditor.cpp
  fanmenuelement.cpp
  fanmenu.cpp
  gitremote.cpp
  identityitem.cpp
  groupgraphicsview.cpp
  newpersondialog.cpp
  grouplistview.cpp
  mainwindow.cpp
  main.cpp
  polkaview.cpp
  polkamodel.cpp
  gitdir.cpp
  gitcommand.cpp
  polkaitemmodel.cpp
  polkaallitemmodel.cpp
  polkapersonsitemmodel.cpp
  personview.cpp
  imageloader.cpp
  pictureselector.cpp
  pictureselectorbutton.cpp
  localpicture.cpp
  regiongrabber.cpp
  trackinggraphicsview.cpp
)

kconfig_add_kcfg_files(polka_bin_SRCS settings.kcfgc )

add_executable(polka_bin ${polka_bin_SRCS})
set_target_properties( polka_bin PROPERTIES OUTPUT_NAME polka )

target_link_libraries(polka_bin polka
  Qt5::Gui
  Qt5::WebKitWidgets
  KF5::CoreAddons
  KF5::KIOCore
  KF5::WidgetsAddons
  KF5::ConfigGui
  KF5::XmlGui
  KF5::KIOFileWidgets
  KF5::KIOWidgets
  KF5::KIONTLM
  KF5::WindowSystem
)

install(TARGETS polka_bin ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES polka.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES polka.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES polkaui.rc  DESTINATION  ${DATA_INSTALL_DIR}/polka )
