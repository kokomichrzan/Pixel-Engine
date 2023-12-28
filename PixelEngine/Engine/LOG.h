#pragma once
//LIBs
#include <string>

//LOG Data
static std::string LogData;
static bool ScrollDown = false;

class LOG
{
public: //Add Log
    void WARNING(const std::string& Value);
    void INFO(const std::string& Value);
    void MESSAGE(const std::string& Value);

public: //Get Log
    const std::string& GetLog();
    bool CheckIfScrollDown();

};