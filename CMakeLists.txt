cmake_minimum_required(VERSION 3.17)
project(Equal)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(SDL_MAIN_HANDLED)

if (WIN32)
    message(STATUS "> Applying windows settings")
    add_compile_options(/EHsc)
endif (WIN32)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "> Applying debug settings")
    add_compile_definitions(DEBUG)
    add_compile_definitions(DEBUG_FPS DEBUG_COLLISION)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

find_package(EnTT CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS "**/*.cpp")
file(GLOB PROJECT_INCLUDES CONFIGURE_DEPENDS "**/*.h" "**/*.hpp")

add_executable(main main.cpp ${PROJECT_SOURCES} ${PROJECT_INCLUDES})
target_link_libraries(main PRIVATE EnTT::EnTT)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(main PRIVATE SDL2::SDL2_image)
target_link_libraries(main PRIVATE SDL2::SDL2_ttf)
target_link_libraries(main PRIVATE pugixml pugixml::shared pugixml::pugixml)
