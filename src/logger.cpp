#include "logger.hpp"

#include <cstdio>
#include <fstream>
#include <iterator>
#include <optional>

#include "fmt/color.h"

LogLevel::LogLevel(Level level) : m_level(level) {}

LogLevel::operator LogLevel::Level() const { return m_level; }

const std::string LogLevel::to_string() const {
    switch (m_level) {
    case Level::Info:
        return "INFO";
    case Level::Debug:
        return "DEBUG";
    case Level::Warn:
        return "WARN";
    case Level::Error:
        return "ERROR";
    case Level::Fatal:
        return "FATAL";
    }
}

fmt::color LogLevel::to_colour() const {
    switch (m_level) {
    case Level::Info:
        return fmt::color::gray;
    case Level::Debug:
        return fmt::color::green;
    case Level::Warn:
        return fmt::color::yellow;
    case Level::Error:
        return fmt::color::orange;
    case Level::Fatal:
        return fmt::color::dark_red;
    }
}

void Logger::set_log(const std::string &log_file_path) {
    m_file = std::fopen(log_file_path.c_str(), "a");
}
