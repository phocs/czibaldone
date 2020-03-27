
file(GLOB tests_src "*.c")
foreach(test_path ${tests_src})
    get_filename_component(srcname ${test_path} NAME)
    get_filename_component(execname ${test_path} NAME_WE)

    add_executable(${execname} ${srcname})

    set_target_properties(
        ${execname} PROPERTIES
        BINARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )
    # target_link_libraries(${execname} PUBLIC _libname_)
    # target_include_directories(${execname} PUBLIC ${CMAKE_BINARY_DIR})
endforeach()
