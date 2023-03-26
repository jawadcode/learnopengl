#include <glad/glad.h>
#include <string>
#include "logger.hpp"

class Program {
  private:
    GLuint m_program_id;
    GLuint m_vertex_shader_id;
    GLuint m_fragment_shader_id;
    const std::string m_vertex_shader;
    const std::string m_fragment_shader;
    Logger &logger;

  public:
    Program(Logger &logger, const std::string &vertex_path, const std::string &fragment_path);
    ~Program();
    void attach();
};
