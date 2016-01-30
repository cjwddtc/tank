AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(bumpcheck_extra SHARED ${SRCLIST})
target_link_libraries(bumpcheck_extra bumpcheck ) 