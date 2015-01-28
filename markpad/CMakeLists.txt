project(kmarkpad)

set (kmarkpad_SRCS
    main.cpp
    mainwindow.cpp
    kmarkpad.cpp
    highlighterbykate.cpp
    htmlgenerator.cpp
)

kde4_add_kcfg_files (kmarkpad_SRCS kmarknote_generalsettings.kcfgc)

kde4_add_executable (kmarkpad ${kmarkpad_SRCS})

include_directories(../marknote/)

target_link_libraries (kmarkpad
                    ${KDE4_KDEUI_LIBS} 
                    ${KDE4_KTEXTEDITOR_LIBS}
                    ${KDE4_KDEWEBKIT_LIBS}  
                    mdcpp
)

install(TARGETS kmarkpad DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS kmarkpad.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kmarkpad.rc DESTINATION ${DATA_INSTALL_DIR}/kmarkpad)
# install( FILES kmarknote_generalsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR} )