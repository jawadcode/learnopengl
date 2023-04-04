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
conan install . --output-folder=build --build=missing
meson configure -Dcpp_std=c++20 ./build/meson-src

cd build
meson setup --native-file conan_meson_native.ini .. meson-src
meson compile -C meson-src

# Windows
./meson-src/learnopengl.exe
# Unices
./meson-src/learnopengl
```
