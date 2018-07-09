project (CellularAutomaton)

# Not ideal to modify CMAKE_MODULE_PATH like this
# but I like to keep 3rdparty packages in a specific location
list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_PATH}/cmake/Modules")

find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	link_directories($ENV{SFML_PATH}/bin)
endif()

file (GLOB_RECURSE CPP_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
		
# Create the executable
add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

