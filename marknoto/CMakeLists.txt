set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

if (WIN32)
    set(marknoto_ICON icon.rc)
endif (WIN32)

set (marknoto_SRCS
   main.cpp
   marknoto.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   iconfilter.cpp
   taglist.cpp
   metadata.cpp
   navpanel.cpp
   listpanel.cpp
   listitemdelegate.cpp
   ../markpado/markpado.cpp
   ../markpado/highlighterbykate.cpp
   ../markpado/htmlgenerator.cpp
   ../markpado/document.cpp
   ../markpado/webpage.cpp
   icon.rc
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
include_directories (${CMAKE_INSTALL_PREFIX}/include/)
target_link_libraries (marknoto
    ${CMAKE_INSTALL_PREFIX}/lib/mdcpp.lib
    C:/local/boost_1_60_0/lib64-msvc-14.0/libboost_regex-vc140-mt-1_60.lib
    Qt5::WebEngineWidgets
    Qt5::WebChannel
    KF5::TextEditor
    KF5::I18n
    KF5::XmlGui
)
elseif (APPLE)
target_link_libraries (marknoto
    mdcpp
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

if(APPLE)
    # own plist template
    set_target_properties (marknoto PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/data/MacOSXBundleInfo.plist.in)

    # the MacOSX bundle display name property (CFBundleDisplayName) is not currently supported by cmake,
    # so has to be set for all targets in this cmake file
    set(MACOSX_BUNDLE_DISPLAY_NAME Marknoto)
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "com.sadhen.kde.Marknoto")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Marknoto")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_DISPLAY_NAME "Marknoto")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_INFO_STRING "Marknoto - Markdown Note-taking Application")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "Marknoto ${KDE_APPLICATIONS_VERSION}")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION "${KDE_APPLICATIONS_VERSION}")
    set_target_properties(marknoto PROPERTIES MACOSX_BUNDLE_COPYRIGHT "2000-2017 Darcy Shen")
endif()

install(TARGETS marknoto ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS marknoto.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES Home.md DESTINATION ${DATA_INSTALL_DIR}/marknoto)
