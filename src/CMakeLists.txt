cmake_minimum_required(VERSION 3.18)
project(engine_project CXX C)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build)


# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

add_library(glad SHARED
            KHR/khrplatform.h
            glad/glad.h
            glad/glad.c)
target_compile_features(glad PUBLIC cxx_std_17)

add_library(lodepng SHARED
                    lodepng.cpp
                    lodepng.h)
target_compile_features(lodepng PUBLIC cxx_std_17)

add_executable(engine_pr

                            main.cpp
                            structs.hxx
                            graphic/graphicinit.cpp
                            graphic/graphicinit.hxx
                            myimgui.h
                            animation.hxx
                            numbers.hxx
                            )

#sdl2
#target_include_directories(game_ship PRIVATE ${SDL2_INCLUDE_DIRS})
#target_link_libraries(game_ship PRIVATE ${SDL2_LIBRARIES})
#target_link_libraries(game_ship PRIVATE SDL2::SDL2 SDL2::SDL2main)
#sdl-ttf
#target_include_directories(game_ship PRIVATE ${SDL_TTF_INCLUDE_DIRS})
#target_link_libraries(game_ship PRIVATE ${SDL_TTF_LIBRARIES})

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(engine_pr PRIVATE SDL2::Main)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(engine_pr PUBLIC SDL2::TTF)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(engine_pr PUBLIC SDL2::Image)

target_link_libraries(engine_pr PUBLIC imgui)
target_link_libraries(engine_pr PRIVATE glad)
target_link_libraries(engine_pr PRIVATE lodepng)

target_compile_features(engine_pr PUBLIC cxx_std_20)


