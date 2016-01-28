AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(core ${SRCLIST})
target_link_libraries(core graphic logic) 