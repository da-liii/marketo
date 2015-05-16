project(kmarkpad)

set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set (kmarkpad_SRCS
    main.cpp
    mainwindow.cpp
    kmarkpad.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
)

add_executable (kmarkpad ${kmarkpad_SRCS})

include_directories(../marknote/)
include_directories( ${QT_INCLUDES} /usr/include/KF5/KDEWebKit)


target_link_libraries (kmarkpad
	${QT_QTWEBKIT_LIBRARIES}
	KF5::TextEditor
	KF5::I18n
	KF5::XmlGui
	KF5::KDELibs4Support
	KF5WebKit
	mdcpp
)

install(TARGETS kmarkpad DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarkpad.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarkpad.rc DESTINATION ${DATA_INSTALL_DIR}/kmarkpad)
# install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

add_subdirectory (css)
add_subdirectory (icons)
