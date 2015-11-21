set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (marknoto_SRCS
   main.cpp
   marknote.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   #terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   ../markpado/markpado.cpp
   ../markpado/highlighterbykate.cpp
   ../markpado/htmlgenerator.cpp
)

# kf5_add_kcfg_files (kmarknote_SRCS kmarknote_generalsettings.kcfgc)

add_executable (marknoto ${marknoto_SRCS})

include_directories (../markpado/)
include_directories( ${QT_INCLUDES} /usr/include/KF5/KDEWebKit)


target_link_libraries (marknoto
    mdcpp
    ${QT_QTWEBKIT_LIBRARIES}
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
    KF5::KDELibs4Support
    KF5WebKit
    mdcpp
)

install(TARGETS marknoto DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS marknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES marknote.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/marknote)
# install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
