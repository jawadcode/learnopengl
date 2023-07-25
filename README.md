# LearnOpenGL

An exercise in learning both OpenGL (through https://learnopengl.com/) and \[modern\] C++ (through suffering).

## Build Instructions:

```sh
# Download & compile any dependencies, then add a bunch of stuff to 'builddir/' that allows meson to locate said dependencies:
conan install . --output-folder=builddir --build=missing

cd builddir

# Create a subdirectory 'meson-src-debug' for debug builds:
meson setup --buildtype=debug --native-file=conan_meson_native.ini -Dcpp_std=c++20 -Db_sanitize=address -Dwarning_level=3 .. meson-src-debug

meson compile -C meson-src-debug

# Final executables:
# Windows: '<project_root>/builddir/meson-src-debug/learnopengl.exe'
# Unix:    '<project_root>/builddir/meson-src-debug/learnopengl'

# Create a subdirectory 'meson-src-release' for release/optimized builds:
meson setup --buildtype=release --native-file=conan_meson_native.ini -Dcpp_std=c++20 -Db_lto=true -Dwarning_level=3 .. meson-src-release

meson compile -C meson-src-release

# Final executables:
# Windows: '<project_root>/builddir/meson-src-release/learnopengl.exe'
# Unix:    '<project_root>/builddir/meson-src-release/learnopengl'
```