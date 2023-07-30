#ifndef LEARNOPENGL_LOGGER_HPP
#define LEARNOPENGL_LOGGER_HPP

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <optional>
#include <source_location>
#include <string>

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <string_view>

class LogLevel {
  public:
    enum Level : std::uint8_t { Info, Debug, Warn, Error, Fatal };

    LogLevel(Level level);
    operator Level() const;

    const std::string to_string() const;
    fmt::color to_colour() const;

  private:
    const Level m_level;
};

class Logger {
  public:
    static Logger &get() {
        static Logger instance;
        return instance;
    }

    void set_log(const std::string &log_file_path);

    void flush();

    template <class... Args>
    void log(const LogLevel level, const std::source_location loc,
             fmt::format_string<Args...> fmt, Args &&...args) {
        auto timestamp =
            fmt::format("{:%FT%TZ}", std::chrono::system_clock::now());

        auto level_str = level.to_string();
        auto level_colour = level.to_colour();

        if (m_file.has_value()) {
            auto file = m_file.value();
            fmt::print(file, "{} [{}] {} @ {}({}:{}) :: ", level_str, timestamp,
                       loc.function_name(), loc.file_name(), loc.line(),
                       loc.column());
            fmt::print(file, fmt, args...);
            fmt::print(file, "\n");
            std::fflush(m_file.value());
        } else {
            fmt::print(fmt::fg(level_colour), level_str);
            fmt::print(" [{}]", timestamp);
            fmt::print(fmt::fg(fmt::color::light_blue), " '{}'",
                       loc.function_name());
            fmt::print("@");
            std::string_view f_sv(loc.file_name());
            fmt::print(fmt::fg(fmt::color::gray), "{}:{}:{}",
                       f_sv.substr(6, f_sv.length() - 6), loc.line(),
                       loc.column());
            fmt::print(" :: ");
            fmt::print(fmt, args...);
            fmt::print("\n");
            fflush(stdout);
        }
    }

  private:
    Logger() = default;
    ~Logger() = default;
    // We do not talk about iostream
    std::optional<std::FILE *> m_file = std::nullopt;
};

#define INIT_LOG(path) Logger::get().set_log(path)

// Because MSVC just *has* to be special
#ifdef _MSC_VER

#define LOG_INFO(fmt, ...)                                                     \
    Logger::get().log(LogLevel::Info, std::source_location::current(), fmt,    \
                      __VA_ARGS__)
#define LOG_DEBUG(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Debug, std::source_location::current(), fmt,   \
                      __VA_ARGS__)
#define LOG_WARN(fmt, ...)                                                     \
    Logger::get().log(LogLevel::Warn, std::source_location::current(), fmt,    \
                      __VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Error, std::source_location::current(), fmt,   \
                      __VA_ARGS__)
#define LOG_FATAL(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Fatal, std::source_location::current(), fmt,   \
                      __VA_ARGS__)

#else

#define LOG_INFO(fmt, ...)                                                     \
    Logger::get().log(LogLevel::Info, std::source_location::current(),         \
                      fmt __VA_OPT__(, ) __VA_ARGS__)
#define LOG_DEBUG(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Debug, std::source_location::current(),        \
                      fmt __VA_OPT__(, ) __VA_ARGS__)
#define LOG_WARN(fmt, ...)                                                     \
    Logger::get().log(LogLevel::Warn, std::source_location::current(),         \
                      fmt __VA_OPT__(, ) __VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Error, std::source_location::current(),        \
                      fmt __VA_OPT__(, ) __VA_ARGS__)
#define LOG_FATAL(fmt, ...)                                                    \
    Logger::get().log(LogLevel::Fatal, std::source_location::current(),        \
                      fmt __VA_OPT__(, ) __VA_ARGS__)

#endif

#if defined(LOGLEVEL_DEBUG)

#undef LOG_INFO
#define LOG_INFO(fmt, ...) static_assert(true)

#elif defined(LOGLEVEL_WARN)

#undef LOG_INFO
#define LOG_INFO(fmt, ...) static_assert(true)

#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) static_assert(true)

#elif defined(LOGLEVEL_ERROR)

#undef LOG_INFO
#define LOG_INFO(fmt, ...) static_assert(true)

#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) static_assert(true)

#undef LOG_WARN
#define LOG_WARN(fmt, ...) static_assert(true)

#endif

#endif /* LEARNOPENGL_LOGGER_HPP */
