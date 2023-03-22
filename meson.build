project('learnopengl', ['c', 'cpp'], default_options : ['c_std=c17', 'cpp_std=c++20'])
glfw = dependency('glfw3', version : '3.3.8')
fmt = dependency('fmt', version : '9.1.0')
sources = ['src/glad.c', 'src/logger.cpp', 'src/window.cpp', 'src/main.cpp']
incdir = include_directories('include')
executable('learnopengl', sources, dependencies : [glfw, fmt], include_directories : incdir)
