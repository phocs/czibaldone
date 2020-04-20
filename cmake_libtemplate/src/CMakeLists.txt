add_library(
    ${PROJECT_NAME}
        syshello.c utils.c
        $<TARGET_OBJECTS:${PROJECT_NAME}_sysdeps>
)

# Build option
target_compile_features(
    ${PROJECT_NAME} PRIVATE
        c_std_11
)

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
        -D_GNU_SOURCE
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic -Wno-unused-parameter
        -ffunction-sections -fdata-sections
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include
        PRIVATE
            ${PROJECT_SOURCE_DIR}/lib/formatter
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/sysdeps
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        formatter
)

add_subdirectory(sysdeps)
