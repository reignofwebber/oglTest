


add_executable(7_transform main.cpp
                         shader.h
                         shader.cpp
                         image_loader.h)

#target_compile_options(7_transform PRIVATE ${GLFW3_CFLAGS})

#target_link_directories(7_transform PRIVATE ${GLFW3_LIBRARY_DIRS})

find_path(STB_IMAGE_PATH stb_image.h)
find_path(GLM_PATH glm/glm.hpp)

target_include_directories(7_transform PRIVATE ${STB_IMAGE_PATH} ${GLM_PATH})
target_link_libraries(7_transform PRIVATE ${OPENGL_LIBRARIES} glew32 glfw3)

message(****${CMAKE_CURRENT_LIST_DIR})
message(****${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_LIST_DIR}/vertex_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/fragment_shader.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/3rdParty/bin/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)

# image
configure_file(${CMAKE_CURRENT_LIST_DIR}/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png COPYONLY)