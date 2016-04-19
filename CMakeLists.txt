cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project (marketo)

if (WIN32)
    find_library(MDCPP NAMES mdcpp
        PATHS D:/kde/kate-windows/release5.6/lib NO_DEFAULT_PATH
    )
else (WIN32)
    add_definitions("-DUNIX")
    set (CMAKE_CXX_FLAGS "-std=c++11")
endif (WIN32)

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
	WebEngineWidgets
)

if (WIN32)
find_package (KF5 REQUIRED COMPONENTS
	I18n
	CoreAddons
	XmlGui
	TextEditor
)
else (WIN32)
find_package (KF5 REQUIRED COMPONENTS
	I18n
	CoreAddons
	XmlGui
	TextEditor
	FileMetaData
)
endif (WIN32)

#include_directories( ${QT_INCLUDES}
#    /usr/include/KF5/KCoreAddons
#    /usr/include/KF5/XmlGui
#    /usr/include/KF5/TextEditor
#    /usr/include/KF5/KI18n
#)

add_subdirectory (markpado)
add_subdirectory (marknoto)