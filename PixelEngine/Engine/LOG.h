#pragma once
//LIBs
#include <string>

//Saved LOG
static std::string LOGDATA;
static bool UpdateScroll = false;

class LOG
{
public: //Methodes
    void WARNING(const std::string& Value);
    void INFO(const std::string& Value);
    void MESSAGE(const std::string& Value);
    std::string GetLog();
    bool GetUpdateScroll();

};