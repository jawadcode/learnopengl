#include <glad/glad.h>
#include <string>
#include "logger.hpp"

class Program {
  private:
    GLuint m_vertex_shader_id;
    GLuint m_fragment_shader_id;
    GLuint m_program_id;
    Logger &logger;

  public:
    Program(Logger &logger, const std::string &vertex_source, const std::string &fragment_source);
    ~Program();
    void link();
    void attach();
};
