


add_executable(11_light main.cpp
                         shader.hpp
                         shader.cpp
                         camera.hpp
                         camera.cpp
                         application.hpp
                         application.cpp
                         image_loader.hpp)

#target_compile_options(11_light PRIVATE ${GLFW3_CFLAGS})

#target_link_directories(11_light PRIVATE ${GLFW3_LIBRARY_DIRS})

find_path(STB_IMAGE_PATH stb_image.h)
find_path(GLM_PATH glm/glm.hpp)

target_include_directories(11_light PRIVATE ${STB_IMAGE_PATH} ${GLM_PATH})
target_link_libraries(11_light PRIVATE ${OPENGL_LIBRARIES} glew32 glfw3)

message(****${CMAKE_CURRENT_LIST_DIR})
message(****${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_LIST_DIR}/light.vs ${CMAKE_CURRENT_BINARY_DIR}/light.vs COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/light.fs ${CMAKE_CURRENT_BINARY_DIR}/light.fs COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/lamp.vs ${CMAKE_CURRENT_BINARY_DIR}/lamp.vs COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/lamp.fs ${CMAKE_CURRENT_BINARY_DIR}/lamp.fs COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/3rdParty/bin/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)

# image
configure_file(${CMAKE_CURRENT_LIST_DIR}/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png COPYONLY)