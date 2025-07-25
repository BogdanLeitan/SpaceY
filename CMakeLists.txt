cmake_minimum_required(VERSION 3.10)

project(spacey C)

set(CMAKE_C_STANDARD 99)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    add_executable(${PROJECT_NAME}
        ../src/input.c 
        ../src/main.c)

    target_link_libraries(${PROJECT_NAME} 
        SDL2::SDL2 
        SDL2_image::SDL2_image 
        SDL2_ttf::SDL2_ttf)

else()
    option(MYGAME_VENDORED "Use vendored SDL libraries" OFF)

    if(MYGAME_VENDORED)
        add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
        add_subdirectory(vendored/sdl_image EXCLUDE_FROM_ALL)
        add_subdirectory(vendored/sdl_ttf EXCLUDE_FROM_ALL)
    else()
        find_package(SDL2 REQUIRED CONFIG)
        find_package(SDL2_image REQUIRED CONFIG)
        find_package(SDL2_ttf REQUIRED CONFIG)
    endif()

    add_executable(${PROJECT_NAME}
        ../src/input.c
        ../src/main.c
    )

    if(TARGET SDL2::SDL2main)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
    endif()

    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
        SDL2::SDL2 
        SDL2_image::SDL2_image 
        SDL2_ttf::SDL2_ttf
    )

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
    )
endif()