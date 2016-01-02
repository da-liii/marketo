file(GLOB PO_FILES *.po)
gettext_create_translations(marknoto.pot ALL ${PO_FILES})

add_custom_target(tr_noto SOURCES marknoto.pot ${PO_FILES})
