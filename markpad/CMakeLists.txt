project(markpad)

find_package (KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

set (markpad_SRCS
    main.cpp
    mainwindow.cpp
    markpad.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
)

kde4_add_executable (markpad ${markpad_SRCS})

include_directories(../marknote/)

target_link_libraries (markpad
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS markpad DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS markpad.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES markpad.rc DESTINATION ${DATA_INSTALL_DIR}/markpad)

add_subdirectory (css)
add_subdirectory (icons)
