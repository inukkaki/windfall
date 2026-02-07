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

Run the following command to generate an executable file in the project
directory:

```
cmake --build build
```
