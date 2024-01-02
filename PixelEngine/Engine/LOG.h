#pragma once
//PCH
#include <pch.h>

class LOG
{
public: //Varibles
    static std::vector<std::string> LogData;
    static bool ScrollDown;

public: //Add Log
    void WARNING(const std::string& Value); //!!!
    void MESSAGE(const std::string& Value); //!!
    void INFO(const std::string& Value);    //!


};