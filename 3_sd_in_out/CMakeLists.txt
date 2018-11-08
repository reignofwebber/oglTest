

add_executable(3_sd_in_out main.cpp)

#target_compile_options(3_sd_in_out PRIVATE ${GLFW3_CFLAGS})

#target_link_directories(3_sd_in_out PRIVATE ${GLFW3_LIBRARY_DIRS})
target_link_libraries(3_sd_in_out PRIVATE ${OPENGL_LIBRARIES} glew32 glfw3)

message(****${CMAKE_CURRENT_LIST_DIR})
message(****${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_LIST_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/3rdParty/bin/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)