set (kmarknote_SRCS
   main.cpp
   kmarknote.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   ../markpad/kmarkpad.cpp
   ../markpad/highlighterbykate.cpp
   ../markpad/htmlgenerator.cpp
)

kde4_add_executable (kmarknote ${kmarknote_SRCS})

include_directories (../markpad/)

target_link_libraries (kmarknote
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS kmarknote DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarknote.rc DESTINATION ${DATA_INSTALL_DIR}/kmarknote)