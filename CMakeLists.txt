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
#add_subdirectory(3_sd_in_out)
#add_subdirectory(4_sd_uniform)
#add_subdirectory(5_shader_extract)
#add_subdirectory(6_texture)
#add_subdirectory(7_transform)
#add_subdirectory(10_camera)
#add_subdirectory(11_light_1)
#add_subdirectory(11_light_2)
#add_subdirectory(12_material)
add_subdirectory(13_lightmap)