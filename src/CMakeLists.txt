cmake_minimum_required(VERSION 3.21)
project(engine_project CXX C)

#set(cmake-build-debug ${CMAKE_CURRENT_SOURCE_DIR}/../build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build)


#install passes
set(CMAKE_INSTALL_BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)




add_library(glad SHARED
            foundation/KHR/khrplatform.h
            foundation/glad/glad.h
            foundation/glad/glad.c)
target_compile_features(glad PUBLIC cxx_std_17)



include_directories("foundation/")

add_executable(engine_pr
                            main.cpp
                            objects/structs.hxx
                            graphic/graphicinit.cpp
                            graphic/graphicinit.hxx
                            myimgui.h
                            animation.hxx
                            objects/numbers.hxx
        objects/basicPerson.cpp objects/basicPerson.h objects/basicObject.cpp objects/basicObject.h objects/basicCamera.cpp objects/basicCamera.h)


#SDL2 main
set(SDL2_DIR            "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/SDL2-2.30.11/cmake")
find_package(SDL2 REQUIRED)


# Add SDL2_image library
set(SDL2_Image_DIR            "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/SDL2_image-2.8.4/cmake")
find_package(SDL2_Image REQUIRED)



# Add SDL2_ttf library
set(SDL2_ttf_DIR            "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/SDL2_ttf-2.24.0/cmake")
find_package(SDL2_ttf REQUIRED)

target_link_libraries(engine_pr PRIVATE
        SDL2::SDL2main SDL2::SDL2
)
target_link_libraries(engine_pr PUBLIC 
SDL2_image::SDL2_image
SDL2_ttf::SDL2_ttf
)

# Add SDL2 CMake modules for ???imgui???
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_link_libraries(imgui PUBLIC SDL2::SDL2main SDL2::SDL2)
target_link_libraries(engine_pr PUBLIC imgui)
target_link_libraries(engine_pr PUBLIC glad)

target_compile_features(engine_pr PUBLIC cxx_std_20)

#static link and don't need to download gcc libtaries
#https://github.com/jtv/libpqxx/issues/341
target_link_options(engine_pr PRIVATE -static -static-libgcc -static-libstdc++)

#copy dll's to build copy, install in clion or run with ???flags???
#https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
install(FILES $<TARGET_RUNTIME_DLLS:glad> TYPE BIN  )
##install(FILES $<TARGET_RUNTIME_DLLS:imgui> TYPE BIN)
install(FILES $<TARGET_RUNTIME_DLLS:engine_pr> TYPE BIN  )

#----------------------
#copy libs to build folder
#https://gist.github.com/seanmiddleditch/c70a4e46ed1b52145c097e4a632172a8

#example of linking sdl2!!!DEVEL!!!
#https://www.reddit.com/r/sdl/comments/134kpd0/how_to_setup_sdl2_sdl_image_with_cmake_on_windows/

#set(SDL2_ttf_DIR            "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/SDL2_ttf-2.22.0/cmake")

#get_filename_component(Location ${SDL2_IMAGE_LIBRARIES} NAME)
#
#string(REPLACE lib "" Location ${Location})
#string(REPLACE dll.a "dll" Location ${Location})
#message("${Location}")
#message(${SDL2_BUILDING_LIBRARY})

