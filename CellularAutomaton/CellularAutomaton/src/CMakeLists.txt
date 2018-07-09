project (CellularAutomaton)

# set(SFML_ROOT "C:\\Users\\jeffe\\dev\\3rdparty\\sfml\\SFML-2.4.2-windows-vc14-64-bit\\SFML-2.4.2")

set (SFML_PATH "C:\\Users\\jeffe\\dev\\3rdparty\\sfml\\SFML-2.4.2-windows-vc14-64-bit\\SFML-2.4.2")
set (SFML_MODULE_PATH "${SFML_PATH}\\cmake\\Modules")

list(APPEND CMAKE_MODULE_PATH "${SFML_MODULE_PATH}")

find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	link_directories(${SFML_PATH}/bin)
endif()


file (GLOB_RECURSE CPP_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
		
# Create the executable
add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

