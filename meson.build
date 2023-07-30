project(
  'learnopengl',
  ['c', 'cpp'],
  default_options: ['c_std=c17', 'cpp_std=c++20', 'warning_level=3']
)

sources = ['src/main.cpp', 'src/glad.c', 'src/logger.cpp', 'src/utils.cpp', 'src/window.cpp']
include = include_directories('include')

glfw = dependency('glfw3', version: '3.3.8')
fmt = dependency('fmt', version: '9.1.0')

executable('learnopengl', sources, dependencies: [glfw, fmt], include_directories: include, native: true)
