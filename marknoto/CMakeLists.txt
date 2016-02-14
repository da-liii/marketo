set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (marknoto_SRCS
   main.cpp
   marknoto.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   iconfilter.cpp
   taglist.cpp
   metadata.cpp
   #terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   listitemdelegate.cpp
   ../markpado/markpado.cpp
   ../markpado/highlighterbykate.cpp
   ../markpado/htmlgenerator.cpp
)

add_executable (marknoto ${marknoto_SRCS})
add_subdirectory (icons)
add_subdirectory (po)

include_directories (../markpado/)
include_directories( ${QT_INCLUDES}
    /usr/include/KF5/KDEWebKit
    /usr/include/KF5/KFileMetaData
    /usr/include/KF5/BalooWidgets)


target_link_libraries (marknoto
    mdcpp
    Qt5::WebKit
    Qt5::WebKitWidgets
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
    KF5::FileMetaData
    KF5WebKit
    mdcpp
)

install(TARGETS marknoto DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS marknoto.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES marknoto.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/marknoto)
install(FILES Home.md DESTINATION ${DATA_INSTALL_DIR}/marknoto)
