# In this CMakeLists.txt we define which files
# are used to compile the application
set(kmarknote_SRCS
   main.cpp
   kmarknote.cpp
   kmarkview.cpp
   mainview.cpp
   noteview.cpp
   terminalview.cpp
)

kde4_add_executable(kmarknote ${kmarknote_SRCS})

target_link_libraries(kmarknote
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS kmarknote DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarknote.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarknote.rc DESTINATION ${DATA_INSTALL_DIR}/KMarkNote)
