#include <glad/glad.h>
#include <string>
#include "logger.hpp"

class Program {
  private:
    Logger &logger;

  public:
    GLuint m_program_id;

    Program(Logger &logger, const std::string &vertex_source,
            const std::string &fragment_source);

    ~Program();

    void use();

    void set_uniform(const std::string &name, GLboolean uniform) const;

    void set_uniform(const std::string &name, GLint uniform) const;

    void set_uniform(const std::string &name, GLfloat uniform) const;
};
