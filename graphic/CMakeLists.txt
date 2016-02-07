include_directories(${PROJECT_SOURCE_DIR}/bumpcheck)
AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(graphic ${SRCLIST})
target_link_libraries(graphic)