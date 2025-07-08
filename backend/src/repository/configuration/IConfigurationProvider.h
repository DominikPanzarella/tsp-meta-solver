#pragma once

#include <string>


class IConfigurationProvider {
public:
    void readConfiguration(const std::string& path);

private:
};
