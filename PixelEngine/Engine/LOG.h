#pragma once
//LIBs
#include <string>

class LOG
{
public: //Varibles
    static std::string LogData;
    static bool ScrollDown;

public: //Add Log
    void WARNING(const std::string& Value); //!!!
    void MESSAGE(const std::string& Value); //!!
    void INFO(const std::string& Value);    //!


};