include_directories(${PROJECT_SOURCE_DIR}/bumpcheck)
AUX_SOURCE_DIRECTORY(. SRCLIST)
add_library(bumpcheck_extra ${SRCLIST})