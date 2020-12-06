cmake_minimum_required(VERSION 3.18)

project(ChickenShooter)

set(SDL2_INCLUDE_DIR D:/libsC++/SDL2/include)
set(SDL2_LIB_DIR D:/libsC++/SDL2/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SOURCE_FILES src/sdl_windows_main.cpp 
src/Renderer/VertexBuffer.cpp
src/Renderer/VertexBuffer.h
src/Renderer/ShaderProgram.h
src/Renderer/ShaderProgram.cpp
src/Renderer/ResourceManager.cpp
src/Renderer/ResourceManager.h
src/Renderer/ElementBuffer.cpp
src/Renderer/ElementBuffer.h
src/Renderer/VertexArray.h
src/Renderer/VertexArray.cpp
src/Resource/stb_image.h
src/Resource/background.h
src/Resource/background.cpp
src/Resource/Hero.h
src/Resource/Hero.cpp
src/Renderer/Texture2D.h
src/Renderer/Texture2D.cpp
src/Resource/Game.cpp
src/Resource/Game.h
src/Renderer/Sprite.h
src/Renderer/Sprite.cpp
src/Renderer/AnimatedSprite.h
src/Renderer/AnimatedSprite.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

include_directories(external/glm)

add_subdirectory(external/glad)
target_link_libraries(ChickenShooter glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)