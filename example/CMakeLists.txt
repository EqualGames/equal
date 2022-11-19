project(example)

file(GLOB_RECURSE SRC_FILES "**.cpp")
file(GLOB_RECURSE INC_FILES "**.h")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE equal)

if (EQ_SHARED)
    file(GLOB_RECURSE DEPENDENCIES "${CMAKE_BINARY_DIR}/equal/*.dll")

    foreach (dep IN LISTS DEPENDENCIES)
        add_custom_command(
                TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dep} $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMENT "> Copying ${dep}"
        )
    endforeach ()
endif (EQ_SHARED)
