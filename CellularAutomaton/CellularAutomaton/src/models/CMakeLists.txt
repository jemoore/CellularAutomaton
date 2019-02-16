file (GLOB_RECURSE CPP_FILES
				${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file (GLOB_RECURSE HPP_FILES
				${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library (models ${CPP_FILES} ${HPP_FILES})

target_include_directories (models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
