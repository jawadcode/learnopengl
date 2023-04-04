project('learnopengl', ['c', 'cpp'], default_options : ['c_std=c17', 'cpp_std=c++20'])
glfw = dependency('glfw3', version : '3.3.8')
fmt = dependency('fmt', version : '9.1.0')
glm = dependency('glm', version : 'cci.20230113')
sources = ['src/main.cpp', 'src/glad.c', 'src/logger.cpp', 'src/window.cpp', 'src/vbo.cpp', 'src/index_buffer.cpp', 'src/program.cpp']
incdir = include_directories('include')
executable('learnopengl', sources, dependencies : [glfw, fmt, glm], include_directories : incdir)
