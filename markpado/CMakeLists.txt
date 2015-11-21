project(markpado)

set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (markpado_SRCS
    main.cpp
    mainwindow.cpp
    markpado.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
)

add_executable (markpado ${markpado_SRCS})

include_directories(../marknote/)
include_directories( ${QT_INCLUDES} /usr/include/KF5/KDEWebKit)


target_link_libraries (markpado
	${QT_QTWEBKIT_LIBRARIES}
	KF5::TextEditor
	KF5::I18n
	KF5::XmlGui
	KF5::KDELibs4Support
	KF5WebKit
	mdcpp
)

install(TARGETS markpado DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS markpado.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES markpado.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/markpado)
# install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

add_subdirectory (css)
add_subdirectory (icons)
