QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.6.sdk

QT       += core gui xml webkit

TARGET = Polka
TEMPLATE = app
INSTALLS=target
DEFINES += MAKE_IT_MEEGO
INCLUDEPATH += ../lib ../microkde meego

SOURCES += main_polka.cpp \
    ../microkde/KDialog.cpp \
    ../microkde/KInputDialog.cpp \
    ../microkde/KJob.cpp \
    ../microkde/KLineEdit.cpp \
    ../microkde/KLocale.cpp \
    ../microkde/KMessageBox.cpp \
    ../microkde/KPushButton.cpp \
    ../microkde/KRandom.cpp \
    ../microkde/KStandardDirs.cpp \
    ../microkde/kio/job.cpp \
    matchlist.cpp \
    searchresultview.cpp \
    searchedit.cpp \
    meegomainwindow.cpp \
    polkaview.cpp \
    polkamodel.cpp \
    overview.cpp \
    grouplistview.cpp \
    groupgraphicsview.cpp \
    personview.cpp \
    historyview.cpp \
    settingswidget.cpp \
    meego/settings.cpp \
    gitremote.cpp \
    newgroupdialog.cpp \
    ../lib/polka/polka.cpp \
    newpersondialog.cpp \
    groupview.cpp \
    gitdir.cpp \
    polkaallitemmodel.cpp \
    polkapersonsitemmodel.cpp \
    polkaitemmodel.cpp \
    gitcommand.cpp \
    localpicture.cpp \
    trackinggraphicsview.cpp \
    identityitem.cpp \
    magicmenuitem.cpp \
    mainmenuitem.cpp \
    groupadderitem.cpp \
    labelitem.cpp \
    fanmenuitem.cpp \
    fanmenuelement.cpp \
    fanmenu.cpp \
    pictureselectorcontrols.cpp \
    pictureselectorbutton.cpp \
    pictureselector.cpp \
    ../lib/polka/htmlrenderer.cpp \
    ../lib/polka/htmlcreator.cpp \
    roundedrectitem.cpp \
    regiongrabber.cpp \
    phoneeditor.cpp \
    linkeditor.cpp \
    commenteditor.cpp \
    buttonitem.cpp \
    addresseditor.cpp \
    addpicturewidget.cpp \
    imageloader.cpp \
    imageloaderfacebook.cpp \
    imageloadertwitter.cpp

HEADERS += \
    ../microkde/kdemacros.h \
    ../microkde/KConfig \
    ../microkde/KDialog.h \
    ../microkde/KGlobal \
    ../microkde/KInputDialog \
    ../microkde/KJob \
    ../microkde/KLineEdit \
    ../microkde/KLocale \
    ../microkde/KMessageBox \
    ../microkde/KPushButton \
    ../microkde/KRandom \
    ../microkde/KStandardDirs.h \
    ../microkde/kio/job.h \
    imageloader.h \
    imageloaderfacebook.h \
    imageloadertwitter.h \
    addpicturewidget.h \
    matchlist.h \
    searchresultview.h \
    searchedit.h \
    polkaview.h \
    meegomainwindow.h \
    meego/settings.h \
    polkamodel.h \
    overview.h \
    grouplistview.h \
    groupview.h \
    groupgraphicsview.h \
    personview.h \
    regiongrabber.h \
    trackinggraphicsview.h \
    settingswidget.h \
    roundedrectitem.h \
    polkapersonsitemmodel.h \
    polkaitemmodel.h \
    polkaallitemmodel.h \
    pictureselectorcontrols.h \
    pictureselectorbutton.h \
    pictureselector.h \
    phoneeditor.h \
    newpersondialog.h \
    newgroupdialog.h \
    mainmenuitem.h \
    magicmenuitem.h \
    localpicture.h \
    linkeditor.h \
    labelitem.h \
    identityitem.h \
    groupadderitem.h \
    gitremote.h \
    gitdir.h \
    gitcommand.h \
    historyview.h \
    fanmenuitem.h \
    fanmenuelement.h \
    fanmenu.h \
    commenteditor.h \
    addresseditor.h \
    buttonitem.h

RESOURCES += \
    ../polka.qrc

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/Polka/bin
    INSTALLS += target
}
