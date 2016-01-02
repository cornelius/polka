set(polka_LIB_SRCS
  htmlrenderer.cpp
  polka.cpp
  htmlcreator.cpp
)

add_library( polka SHARED ${polka_LIB_SRCS} )

target_link_libraries( polka
  Qt5::Core
  Qt5::Xml
  KF5::I18n
)

set_target_properties( polka PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install( TARGETS polka ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES
  htmlrenderer.h
  polka.h
  htmlcreator.h
  polka_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/polka
)
