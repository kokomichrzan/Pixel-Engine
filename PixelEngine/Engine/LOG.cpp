#include "LOG.h"

std::vector<std::string> LOG::LogData;
bool LOG::ScrollDown;

//Add Log
void LOG::WARNING(const std::string& Value){
    LogData.emplace_back("[WARNING] " + Value + "\n");
    LOG::ScrollDown = true;

}

void LOG::MESSAGE(const std::string& Value){
    LogData.emplace_back("[MESSAGE] " + Value + "\n");
    LOG::ScrollDown = true;

}

void LOG::INFO(const std::string& Value){
    LogData.emplace_back("[INFO] " + Value + "\n");
    LOG::ScrollDown = true;

}

