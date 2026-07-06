find_package(Threads REQUIRED)
set(MANDELBROT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(MANDELBROT_RUNTIME_DIR "${PROJECT_BINARY_DIR}")
set(MANDELBROT_IMAGES_DIR "${PROJECT_SOURCE_DIR}/images")

add_custom_target(create_output_dirs ALL
    COMMAND "${CMAKE_COMMAND}" -E make_directory
            "${MANDELBROT_RUNTIME_DIR}"
            "${MANDELBROT_IMAGES_DIR}"
)

add_executable(mandelbrot_single_thread
    main_single_thread.cpp
    bitmap.cpp
    mandelbrot_single_thread.cpp
)
target_include_directories(mandelbrot_single_thread PRIVATE "${MANDELBROT_INCLUDE_DIR}")
set_target_properties(mandelbrot_single_thread PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${MANDELBROT_RUNTIME_DIR}"
    DEBUG_POSTFIX "_debug"
)
add_dependencies(mandelbrot_single_thread create_output_dirs)
add_custom_target(single_thread DEPENDS mandelbrot_single_thread)

add_executable(mandelbrot_parallel
    main_parallel.cpp
    bitmap.cpp
    mandelbrot_parallel.cpp
)
target_include_directories(mandelbrot_parallel PRIVATE "${MANDELBROT_INCLUDE_DIR}")
target_link_libraries(mandelbrot_parallel PRIVATE Threads::Threads)
set_target_properties(mandelbrot_parallel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${MANDELBROT_RUNTIME_DIR}"
    DEBUG_POSTFIX "_debug"
)
add_dependencies(mandelbrot_parallel create_output_dirs)
add_custom_target(parallel DEPENDS mandelbrot_parallel)
