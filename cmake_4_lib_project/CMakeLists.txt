cmake_minimum_required(VERSION 3.12)

# Disable in-source builds to prevent source tree corruption.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "FATAL: In-source builds are not allowed.
    You should create a separate directory for build files.")
endif()

project(
    _libname_
	VERSION 0.0.1
	DESCRIPTION ""
	HOMEPAGE_URL ""
	LANGUAGES C
)

set(CMAKE_C_EXTENSIONS TRUE)

include(GNUInstallDirs)

add_definitions(-D_GNU_SOURCE)
add_compile_options(-Wall -Wextra -Werror -pedantic -Wno-unused-parameter)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(lib)
add_subdirectory(test)

add_subdirectory(man)

if(NOT TARGET uninstall)
    configure_file(
        ${CMAKE_CONFIG_DIR}/cmake_uninstall.cmake.in
        ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
        IMMEDIATE @ONLY
    )

    add_custom_target(
        uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
    )
endif()
