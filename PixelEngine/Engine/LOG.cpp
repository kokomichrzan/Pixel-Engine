#include "LOG.h"

std::string LOG::LogData;
bool LOG::ScrollDown;

//Add Log
void LOG::WARNING(const std::string& Value){
    LOG::LogData += "[WARNING] " + Value + "\n";
    LOG::ScrollDown = true;

}

void LOG::INFO(const std::string& Value){
    LOG::LogData += "[INFO] " + Value + "\n";
    LOG::ScrollDown = true;

}

void LOG::MESSAGE(const std::string& Value){
    LOG::LogData += "[MESSAGE] " + Value + "\n";
    LOG::ScrollDown = true;

}