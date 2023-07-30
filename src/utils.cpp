#include "utils.hpp"

#include <cstdlib>
#include <optional>
#include <string>
#include <string_view>

std::optional<const std::string> get_env(const std::string &key) {
    const char *var = std::getenv(key.c_str());
    return var == nullptr ? std::nullopt : std::optional(var);
}
