cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project (kmarknote)

set (CMAKE_CXX_FLAGS "-std=c++11")

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
	CoreAddons
	XmlGui
	TextEditor
	KDELibs4Support
)

add_subdirectory (markpad)
add_subdirectory (marknote)
