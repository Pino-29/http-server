//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_CONFIG_H
#define HTTP_SERVER_STARTER_CPP_CONFIG_H

#include <optional>
#include <string>
#include <unordered_map>

class Config : public std::unordered_map<std::string, std::string>
{
public:
    static Config& instance();

    [[nodiscard]] std::string get(const std::string& key, const std::string& defaultValue = "") const;

    [[nodiscard]] std::optional<std::string> tryGet(const std::string& key) const;

    void set(const std::string& key, const std::string& value);

    void lock(); // Prevent further mutation

private:
    bool m_locked { false };

    Config() = default;
};

#endif //HTTP_SERVER_STARTER_CPP_CONFIG_H
