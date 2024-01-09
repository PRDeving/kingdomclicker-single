file(GLOB_RECURSE SRC_FILES "*.cpp")
add_definitions(-DRAYLIB)
add_library(engine ${SRC_FILES})
