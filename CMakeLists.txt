cmake_minimum_required(VERSION 3.17)
project(Equal)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    message(STATUS "> Applying windows settings")
    add_compile_options(/EHsc)
endif (WIN32)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "> Applying debug settings")
    add_compile_definitions(DEBUG DEV_TOOLS)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

find_package(EnTT CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS
        "**/*.cpp"
        "**/**/*.cpp"
        "**/**/**/*.cpp"
        )
file(GLOB PROJECT_INCLUDES CONFIGURE_DEPENDS
        "**/*.h"
        "**/**/*.h"
        "**/**/**/*.h"
        )

add_executable(main
        main.cpp
        ${PROJECT_SOURCES}
        ${PROJECT_INCLUDES}
        )

target_link_libraries(main PRIVATE EnTT::EnTT)
target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-main)
target_link_libraries(main PRIVATE imgui::imgui)
target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(main PRIVATE fmt::fmt-header-only)
target_link_libraries(main PRIVATE pugixml pugixml::shared pugixml::pugixml)
