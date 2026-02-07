# windfall

under construction

# How to build

This project uses CMake to make a buildsystem.

The directory structure is as follows:
-   `build/`: Build directory. This is to be created by running the CMake
    commands mentioned later.
-   `src/`: Source directory.

First of all, generate a buildsystem by specifying both the source and build directories:
```
cmake -G Ninja -S . -B build
```

This project uses SDL2 to make a GUI application. Make sure to set PATH_TO_SDL2
to the path to a directory that contains SDL2 libraries before building the
programs:
```
cmake build -DPATH_TO_SDL2=/path/to/SDL2
```

Run the following command to generate an executable output in the project
directory:
```
cmake --build build
```

To execute the output, the following shared libraries must be in the same
directory where the output is:
-   SDL2.dll
-   SDL2_image.dll
