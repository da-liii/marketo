file(GLOB PO_FILES *.po)
gettext_create_translations(markpado.pot ALL ${PO_FILES})

add_custom_target(tr_pado SOURCES markpado.pot ${PO_FILES})
