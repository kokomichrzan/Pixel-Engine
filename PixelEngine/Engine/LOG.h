#pragma once
//Libs
#include <vector>
#include <string>

class LOG
{
public: //Varibles
    static std::vector<const char*> LogData;
    static bool ScrollDown;

public: //Add Log
    void WARNING(const char* Value); //!!!
    void MESSAGE(const char* Value); //!!
    void INFO(const char* Value);    //!


};