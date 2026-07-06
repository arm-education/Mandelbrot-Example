find_package(GTest REQUIRED)

add_executable(mandelbrot_unit_tests
    mandelbrot_tests.cpp
    "${PROJECT_SOURCE_DIR}/src/bitmap.cpp"
    "${PROJECT_SOURCE_DIR}/src/mandelbrot_single_thread.cpp"
)

target_include_directories(mandelbrot_unit_tests PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

set_target_properties(mandelbrot_unit_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_compile_definitions(mandelbrot_unit_tests PRIVATE
    MANDELBROT_TEST_OUTPUT_DIR="${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(mandelbrot_unit_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mandelbrot_unit_tests)
