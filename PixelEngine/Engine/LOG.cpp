#include "LOG.h"

void LOG::WARNING(const std::string& Value){
    LOGDATA += "[WARNING] " + Value + "\n";
    UpdateScroll = true;
}

void LOG::INFO(const std::string& Value){
    LOGDATA += "[INFO] " + Value + "\n";
    UpdateScroll = true;
}

void LOG::MESSAGE(const std::string& Value){
    LOGDATA += "[MESSAGE] " + Value + "\n";
    UpdateScroll = true;
}

std::string LOG::GetLog() { return LOGDATA; };

bool LOG::GetUpdateScroll(){
    bool State = UpdateScroll;
    UpdateScroll = false;
    return State;
}