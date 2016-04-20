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
   ../markpado/document.cpp
)
qt5_add_resources(marknoto_SRCS data/marknoto.qrc)

add_executable (marknoto ${marknoto_SRCS})
add_subdirectory (icons)
add_subdirectory (po)

include_directories (../markpado/)
include_directories( ${QT_INCLUDES}
    /usr/include/KF5/KDEWebKit
    /usr/include/KF5/KFileMetaData
    /usr/include/KF5/BalooWidgets)


if (WIN32)
include_directories (D:/kde/kate-windows/release5.6/include/)
target_link_libraries (marknoto
    D:/kde/kate-windows/release5.6/lib/mdcpp.lib
    C:/local/boost_1_60_0/lib64-msvc-14.0/libboost_regex-vc140-mt-1_60.lib
    Qt5::WebEngineWidgets
    Qt5::WebChannel
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
)
else (WIN32)
target_link_libraries (marknoto
    mdcpp
    Qt5::WebEngineWidgets
    Qt5::WebChannel
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
    KF5::FileMetaData
)
endif (WIN32)

install(TARGETS marknoto DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS marknoto.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES Home.md DESTINATION ${DATA_INSTALL_DIR}/marknoto)
