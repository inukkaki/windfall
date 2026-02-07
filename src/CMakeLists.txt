# Output an executable file in the project directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Target: windfall
add_executable(windfall
    main.cpp
)
target_compile_features(windfall PUBLIC cxx_std_23)
