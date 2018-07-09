cmake_minimum_required (VERSION 3.5)

if (WIN32)
	add_definitions(-DCMAKE_GENERATOR_PLATFORM=x64)
endif (WIN32)

project (CellularAutomaton)

# Add sub directories
add_subdirectory(CellularAutomaton)

