project (kmarknote)

set (CMAKE_CXX_FLAGS "-std=c++14")

find_package (KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

add_subdirectory (icons)
add_subdirectory (markpad)
add_subdirectory (marknote)
