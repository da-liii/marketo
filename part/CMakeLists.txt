set(marketopart_SRCS
	part.cpp
)
add_library (marketopart MODULE ${marketopart_SRCS})

target_link_libraries(marketopart
	KF5::Parts
)

install (TARGETS marketopart DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install (FILES marketopart.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
