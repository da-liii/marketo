project(markpado)

set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (markpado_SRCS
    main.cpp
    mainwindow.cpp
    markpado.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
	document.cpp
	webpage.cpp
)
qt5_add_resources(markpado_SRCS data/markpado.qrc)

add_executable (markpado ${markpado_SRCS})

include_directories(../marknote/)

if (WIN32)
include_directories(D:/kde/kate-windows/release5.6/include/)
target_link_libraries (markpado
    Qt5::WebEngineWidgets
	Qt5::WebChannel
	KF5::TextEditor
	KF5::I18n
	KF5::XmlGui
	C:/local/boost_1_60_0/lib64-msvc-14.0/libboost_regex-vc140-mt-1_60.lib
	D:/kde/kate-windows/release5.6/lib/mdcpp.lib
)
else (WIN32)
target_link_libraries (markpado
    Qt5::WebEngineWidgets
	Qt5::WebChannel
	KF5::TextEditor
	KF5::I18n
	KF5::XmlGui
	KF5KIOFileWidgets
	mdcpp
)
endif (WIN32)

install(TARGETS markpado RUNTIME DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS markpado.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

add_subdirectory (icons)
add_subdirectory (kate-commonmark)
add_subdirectory (po)
