set (marknote_SRCS
   main.cpp
   marknote.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   ../markpad/markpad.cpp
   ../markpad/highlighterbykate.cpp
   ../markpad/htmlgenerator.cpp
)

kde4_add_executable (marknote ${marknote_SRCS})

include_directories (../markpad/)

target_link_libraries (marknote
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS marknote DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS marknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES marknote.rc DESTINATION ${DATA_INSTALL_DIR}/marknote)
