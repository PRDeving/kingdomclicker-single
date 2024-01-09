file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(raid ${SOURCES})
target_link_libraries(raid engine ${EXTRA_LIBS})
