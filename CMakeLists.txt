cmake_minimum_required(VERSION 3.8)

project(oglTest)

#find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

#pkg_check_modules(GLFW3 glfw3)
#find_package(GLEW)


include_directories(${CMAKE_SOURCE_DIR}/3rdParty/include)
link_directories(${CMAKE_SOURCE_DIR}/3rdParty/lib)

###
#add_subdirectory(1_triangle)
#add_subdirectory(2_rectangle)
add_subdirectory(3_sd_in_out)
