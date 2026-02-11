# Output an executable file in the project directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Target: windfall
add_executable(windfall
    main.cpp

    interface/keyboard.cpp

    routine/debug.cpp
    routine/event.cpp

    system/assert.cpp
    system/config.cpp
    system/launch.cpp
    system/modal.cpp
    system/winfunc.cpp

    time/framerate.cpp
    time/timer.cpp
)
target_compile_features(windfall PUBLIC cxx_std_23)
target_include_directories(windfall
    PUBLIC
        ${PATH_TO_SDL2}/include
        ${PROJECT_SOURCE_DIR}/src
)
target_link_directories(windfall PUBLIC ${PATH_TO_SDL2}/lib)
target_link_libraries(windfall PUBLIC ${SDL2_LIBS})
target_compile_definitions(windfall PUBLIC USE_ASSERT_IN_GUI)
