set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (kmarknote_SRCS
   main.cpp
   kmarknote.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   #terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   ../markpad/kmarkpad.cpp
   ../markpad/highlighterbykate.cpp
   ../markpad/htmlgenerator.cpp
)

# kf5_add_kcfg_files (kmarknote_SRCS kmarknote_generalsettings.kcfgc)

add_executable (kmarknote ${kmarknote_SRCS})

include_directories (../markpad/)
include_directories( ${QT_INCLUDES} /usr/include/KF5/KDEWebKit)


target_link_libraries (kmarknote
    mdcpp
    ${QT_QTWEBKIT_LIBRARIES}
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
    KF5::KDELibs4Support
    KF5WebKit
    mdcpp
)

install(TARGETS kmarknote DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarknote.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kmarknote)
# install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
