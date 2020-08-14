cmake_minimum_required(VERSION 3.9)

project(Pong)

# todo: build this project in different bitness 32 or 64
#set(CMAKE_C_FLAGS   -m32)
#set(CMAKE_CXX_FLAGS -m32)

#set(CMAKE_EXE_LINKER_FLAGS_INIT    -m32)
#set(CMAKE_SHARED_LINKER_FLAGS_INIT -m32)
#set(CMAKE_MODULE_LINKER_FLAGS_INIT -m32)

math(EXPR bitness "${CMAKE_SIZEOF_VOID_P} * 8")
message("${bitness}-bit build")


if(WIN32)
    #Folder with GLFW and GLEW
    set(DEPENDENCIES_PATH dependencies)

    set(LIBRARIES_DEPENDECIES ${DEPENDENCIES_PATH}/bin)
    set(INCLUDE_DEPENDECIES ${DEPENDENCIES_PATH}/include)

    INCLUDE_DIRECTORIES(${INCLUDE_DEPENDECIES})
    LINK_DIRECTORIES(${LIBRARIES_DEPENDECIES})

elseif(UNIX)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    include_directories(${GLFW_INCLUDE_DIRS})

endif()

set(SOURCES src/main.cpp
   src/engine/window/main_window.h
   src/engine/window/main_window.cpp
   src/engine/types/color.h
   src/engine/types/color.cpp
   src/engine/style/colors.h
   src/engine/shader/shader.h
   src/engine/scene/scene.h
   src/engine/scene/scene.cpp
   src/engine/scene/mesh.h
   src/engine/scene/mesh.cpp

   )

set(SHADERS src/shaders/default.vert
    src/shaders/default.frag
    )

add_executable(pong_the_game ${SOURCES} ${SHADERS})

set_target_properties(pong_the_game PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall -Wextra -Wpedantic
)

add_custom_command(TARGET pong_the_game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/shaders/
                   ${CMAKE_CURRENT_BINARY_DIR}/shaders)

#file(COPY ${CMAKE_SOURCE_DIR}/src/shaders/ DESTINATION ${CMAKE_BUILD_DIRECTORY}/shaders)

if(WIN32)
    target_link_libraries(pong_the_game glew32s glfw3 opengl32)

elseif(UNIX)
    target_link_libraries(pong_the_game GLEW::GLEW ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES})

endif()


