AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(bumpcheck_extra ${SRCLIST})
target_link_libraries(bumpcheck_extra bumpcheck ) 