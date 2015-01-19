# In this CMakeLists.txt we define which files
# are used to compile the application
set(kmarknote_SRCS
   main.cpp
   kmarknote.cpp
   kmarkpad.cpp
   mainview.cpp
   noteview.cpp
   panel.cpp
   terminalpanel.cpp
   navpanel.cpp
   listpanel.cpp
   highlighterbykate.cpp
   htmlgenerator.cpp
)

kde4_add_kcfg_files(kmarknote_SRCS kmarknote_generalsettings.kcfgc)

kde4_add_executable(kmarknote ${kmarknote_SRCS})

target_link_libraries(kmarknote
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS kmarknote DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarknote.rc DESTINATION ${DATA_INSTALL_DIR}/kmarknote)
install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
