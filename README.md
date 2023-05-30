# learnopengl

Following along with LearnOpenGL but with a few added abstractions and niceties

# Build dependencies:
* Meson
* Conan
* CMake (to compile some the dependencies)
* pkg-config (so meson can find dependencies)

# Runtime dependencies:

None, other than OpenGL itself

# How to Build:

```bash
conan install . --output-folder=builddir --build=missing

cd builddir
# Debug
meson setup --buildtype=debug --native-file=conan_meson_native.ini -Dcpp_std=c++20 -Db_sanitize=address -Dwarning_level=3 .. meson-src-debug
meson compile -C meson-src-debug
# Release
meson setup --buildtype=release -Dcpp_std=c++20 -Db_lto=true -Dwarning_level=3 --native-file conan_meson_native.ini .. meson-src-release
meson compile -C meson-src-release

# Windows
./meson-src/learnopengl.exe
# Unix
./meson-src/learnopengl
```
