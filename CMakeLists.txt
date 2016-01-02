cmake_minimum_required(VERSION 3.3.2)
set(QT_MIN_VERSION "5.3.0")

project(polka)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Xml Gui WebKitWidgets)

find_package(KF5 REQUIRED COMPONENTS
  I18n
  Config
  CoreAddons
  KIO
  WidgetsAddons
  XmlGui
  WindowSystem
  DocTools
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory( doc )
add_subdirectory( lib/polka )
add_subdirectory( src )
add_subdirectory( icons )
add_subdirectory( pics )
