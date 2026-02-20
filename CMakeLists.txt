cmake_minimum_required(VERSION 3.30)
project(RacingGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(glfw3 REQUIRED)

find_package(GLUT REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ASSIMP REQUIRED assimp)

include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})

#find_package(glm REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MY_HEADER_FILES
        src/window.h
        src/EngineCore.h
        src/object.h
        src/shader.h
        src/renderable.h
        src/movable.h
        src/mesh.h
        src/camera.h
        src/controllable.h
        src/cube.h
        src/materialMesh.h
        src/grid.h
        src/stb_image.h
        src/texture.h
        src/rotatedCube.h
        src/texturedCube.h
        src/model.h


)

set(MY_SOURCE_FILES
        src/window.cpp
        src/main.cpp
        src/EngineCore.cpp
        src/object.cpp
        src/shader.cpp
        src/renderable.cpp
        src/movable.cpp
        src/mesh.cpp
        src/camera.cpp
        src/controllable.cpp
        src/cube.cpp
        src/materialMesh.cpp
        src/grid.cpp
        src/texture.cpp
        src/rotatedCube.cpp
        src/texturedCube.cpp
        src/model.cpp

)


add_executable(RacingGame
        ${MY_HEADER_FILES}
        ${MY_SOURCE_FILES}
)
target_link_libraries(RacingGame
        ${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
        ${GLUT_glut_LIBRARY}
        glfw
        ${ASSIMP_LIBRARIES}


)
