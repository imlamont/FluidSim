cmake_minimum_required(VERSION 3.25)
project(FluidSim)

### compilation ###

# collect source files from src directory
set(SRC_DIR ./src)
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

# put source files into executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} "${SRC_FILES}")

### libraries ###

# ezgl
add_subdirectory(./lib/ezgl)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ./lib/ezgl/Debug/)
target_link_libraries(${PROJECT_NAME} ezgl)
include_directories(./lib/ezgl/)
# include_directories(./lib/ezgl/)

# fltk
add_subdirectory(./lib/fltk)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ./lib/fltk/lib/Debug/)
target_link_libraries(${PROJECT_NAME} fltk)
target_link_libraries(${PROJECT_NAME} fltk_gl)
include_directories(./lib/fltk/)
