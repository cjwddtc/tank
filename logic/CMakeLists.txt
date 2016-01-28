AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(logic ${SRCLIST})
target_link_libraries(logic bumpcheck bumpcheck_extra)