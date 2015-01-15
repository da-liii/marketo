project(kmarknote CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

#add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
