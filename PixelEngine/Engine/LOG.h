#pragma once
#include <string>

static std::string LOGDATA;

class LOG
{
public:
    void WARNING(std::string Value);
    void INFO(std::string Value);
    void MESSAGE(std::string Value);
    std::string GETLOG();

};