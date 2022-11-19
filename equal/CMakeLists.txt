project(equal)

if (EQ_SHARED)
    message(STATUS "> Configuring shared library")
    set(LIB_TYPE "SHARED")

    # equal
    add_compile_definitions(EQ_DLL_EXPORT)

    # entt
    add_compile_definitions(ENTT_API_EXPORT)
else (EQ_SHARED)
    message(STATUS "> Configuring static library")
    set(LIB_TYPE "STATIC")
    set(LIB_POSTFIX "-s")
endif (EQ_SHARED)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES "**.cpp")
file(GLOB_RECURSE INC_FILES "**.h")

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SRC_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        RELEASE_POSTFIX "${LIB_POSTFIX}"
        DEBUG_POSTFIX "${LIB_POSTFIX}-d"
)

target_include_directories(${PROJECT_NAME} PUBLIC "../vendor/entt/src")
target_link_directories(${PROJECT_NAME} PUBLIC "../vendor/entt/src")

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml pugixml::shared pugixml::pugixml)
