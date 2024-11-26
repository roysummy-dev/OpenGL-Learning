cmake_minimum_required(VERSION 3.23)
project(OpenGL_Learning)
set(CMAKE_CXX_STANDARD 14)


find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${ROOT_DIR}/3rd/glfw)

#set(OPENGL_LEARN_SRC src/Application.cpp src/Renderer.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp)
#message(${OPENGL_LEARN_SRC})
aux_source_directory(${ROOT_DIR}/src/ OPENGL_LEARN_SRC)

add_executable(OpenGL_Learning ${OPENGL_LEARN_SRC})


target_include_directories(OpenGL_Learning PUBLIC
        ${ROOT_DIR}/3rd/include
        ${ROOT_DIR}/3rd/include/stb_image)

target_link_directories(OpenGL_Learning PUBLIC
        ${ROOT_DIR}/3rd/libs)

target_link_libraries(OpenGL_Learning
        ${OPENGL_LIBRARIES}
        glfw
        GLEW)