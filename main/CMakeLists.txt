include_directories(${PROJECT_SOURCE_DIR}/bumpcheck)
AUX_SOURCE_DIRECTORY(. SRCLIST)
add_executable(main ${SRCLIST})
target_link_libraries(main graphic core)