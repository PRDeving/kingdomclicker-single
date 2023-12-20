file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(kingdomclicker ${SOURCES})
target_link_libraries(kingdomclicker engine ${EXTRA_LIBS})
