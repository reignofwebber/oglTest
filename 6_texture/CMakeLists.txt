


add_executable(6_texture main.cpp
                         shader.h
                         shader.cpp
                         image_loader.h)

#target_compile_options(6_texture PRIVATE ${GLFW3_CFLAGS})

#target_link_directories(6_texture PRIVATE ${GLFW3_LIBRARY_DIRS})

find_path(STB_IMAGE_PATH stb_image.h)

target_include_directories(6_texture PRIVATE ${STB_IMAGE_PATH})
target_link_libraries(6_texture PRIVATE ${OPENGL_LIBRARIES} glew32 glfw3)

message(****${CMAKE_CURRENT_LIST_DIR})
message(****${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_LIST_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/3rdParty/bin/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)

# image
configure_file(${CMAKE_CURRENT_LIST_DIR}/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png COPYONLY)