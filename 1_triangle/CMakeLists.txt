

add_executable(1_triangle main.cpp)

#target_compile_options(1_triangle PRIVATE ${GLFW3_CFLAGS})

#target_link_directories(1_triangle PRIVATE ${GLFW3_LIBRARY_DIRS})
target_link_libraries(1_triangle PRIVATE ${OPENGL_LIBRARIES} glew32 glfw3)


configure_file(${CMAKE_CURRENT_LIST_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/3rdParty/bin/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)