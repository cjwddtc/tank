AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(core ${SRCLIST})
target_link_libraries(core Showmanage bumpcheck bumpcheck_extra)