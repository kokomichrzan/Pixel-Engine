#include "LOG.h"

std::vector<const char*> LOG::LogData;
bool LOG::ScrollDown;

//Add Log
void LOG::WARNING(const char* Value){
    LogData.emplace_back("[WARNING] " + *Value);
    LOG::ScrollDown = true;

}

void LOG::MESSAGE(const char* Value){
    LogData.emplace_back("[MESSAGE] " + *Value);
    LOG::ScrollDown = true;

}

void LOG::INFO(const char* Value){
    LogData.emplace_back("[INFO] " + *Value);
    LOG::ScrollDown = true;

}

