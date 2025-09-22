//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#include "core/config.hpp"

#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

Config& Config::instance()
{
    static Config cfg {};
    return cfg;
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const
{
    auto it = find(key);
    return it != end() ? it->second : defaultValue;
}

std::optional<std::string> Config::tryGet(const std::string& key) const
{
    auto it = find(key);
    return it != end() ? std::optional<std::string> { it->second } : std::nullopt;
}

void Config::set(const std::string& key, const std::string& value)
{
    if (m_locked)
    {
        throw std::runtime_error("Config is locked. Cannot modify key: " + key);
    }
    (*this)[key] = value;
}

void Config::lock()
{
    m_locked = true;
}
