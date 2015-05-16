cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(kmarkpad)

find_package (ECM 1.7.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
include (FeatureSummary)
include (ECMAddAppIcon)
include (KDEInstallDirs)
include (KDECMakeSettings)
include (KDECompilerSettings)
include (ECMInstallIcons)

find_package(Qt5 REQUIRED
	Core
	WebKit
	WebKitWidgets
)
find_package(KF5WebKit)
find_package (KF5 REQUIRED COMPONENTS
	I18n
	TextEditor
	XmlGui
	KDELibs4Support
)
# include (KDE4Defaults)

include_directories( ${QT_INCLUDES} )

set (kmarkpad_SRCS
    main.cpp
    mainwindow.cpp
    kmarkpad.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
)

# kde4_add_kcfg_files (kmarkpad_SRCS kmarknote_generalsettings.kcfgc)

add_executable (kmarkpad ${kmarkpad_SRCS})

include_directories(../marknote/
    /usr/include/KF5/KDEWebKit
)

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
