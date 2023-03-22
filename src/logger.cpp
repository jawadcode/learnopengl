#include "logger.hpp"

#include <fstream>
#include <chrono>
#include <fmt/chrono.h>
#include <fmt/color.h>

Logger::Logger()
    : m_to_file(false), m_out(std::ostream_iterator<char>(std::cout)) {}

Logger::Logger(const std::string &path) : m_to_file(true) {
    std::ofstream out_file;
    out_file.open(path);
    m_out = *new std::ostream_iterator<char>(out_file);
}
