AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(core ${SRCLIST})
target_link_libraries(core graphic bumpcheck bumpcheck_extra) 
#cotire(core)