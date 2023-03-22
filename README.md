# learnopengl

Me following along with LearnOpenGL but with a few added abstractions and niceties

# Build dependencies:
* Meson
* Conan

# Runtime dependencies:

None, other than opengl

# How to Build:

```bash
conan install . --output-folder=build --build=missing
cd build
meson setup --native-file conan_meson_native.ini .. meson-src
meson compile -C meson-src
# Windows
./meson-src/learnopengl.exe
# Unices
./meson-src/learnopengl
```
