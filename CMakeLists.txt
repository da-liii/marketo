cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project (marketo)

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
)

include_directories( ${QT_INCLUDES}
    /usr/include/KF5/KDEWebKit
    /usr/include/KF5/KCoreAddons
    /usr/include/KF5/XmlGui
    /usr/include/KF5/TextEditor
    /usr/include/KF5/KI18n
)

add_subdirectory (markpado)
add_subdirectory (marknoto)
