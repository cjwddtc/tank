AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(core ${SRCLIST})
target_link_libraries(core bumpcheck bumpcheck_extra)