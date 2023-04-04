#include <iostream>
#include <iterator>
#include <chrono>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

#pragma once

enum class LogLevel {
    Info,
    Debug,
    Warning,
    Error,
    Fatal,
};

class Logger {
  private:
    bool m_to_file;
    std::ostream_iterator<char> m_out = std::ostream_iterator<char>(std::cout);

  public:
    Logger();

    Logger(const std::string &path);

    template <class... Args>
    void log(LogLevel level, std::string file_name, int line_num,
             fmt::format_string<Args...> fmt, Args &&...args) {

        auto now = std::chrono::system_clock::now();
        auto timestamp = fmt::format("{:%FT%TZ}", now);
        std::string level_str;
        switch (level) {
        case LogLevel::Info:
            level_str = "INFO ";
            break;
        case LogLevel::Debug:
            level_str = "DEBUG";
            break;
        case LogLevel::Warning:
            level_str = "WARN ";
            break;
        case LogLevel::Error:
            level_str = "ERROR";
            break;
        case LogLevel::Fatal:
            level_str = "FATAL";
            break;
        }
        if (m_to_file) {
            fmt::format_to(m_out, "{} ", level_str);
        } else {
            fmt::color level_color;
            switch (level) {
            case LogLevel::Info:
                level_color = fmt::color::gray;
                break;
            case LogLevel::Debug:
                level_color = fmt::color::green;
                break;
            case LogLevel::Warning:
                level_color = fmt::color::yellow;
                break;
            case LogLevel::Error:
                level_color = fmt::color::orange;
                break;
            case LogLevel::Fatal:
                level_color = fmt::color::dark_red;
                break;
            }
            fmt::format_to(m_out, fg(level_color) | fmt::emphasis::bold, "{} ",
                           level_str);
        }
        fmt::format_to(m_out, "[{}] ", timestamp);
        fmt::format_to(m_out, fg(fmt::color::gray), "{}:{} ", file_name,
                       line_num);
        fmt::format_to(m_out, fmt, args...);
        fmt::format_to(m_out, "\n");
    }
};

// Because MSVC just *has* to be special
#ifdef _MSC_VER
#define LOG(level, fmt, ...)                                                   \
    (LOGGER).log(level, __FILE__, __LINE__, fmt, __VA_ARGS__)
#else
#define LOG(level, fmt, ...)                                                   \
    (LOGGER).log(level, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#endif
