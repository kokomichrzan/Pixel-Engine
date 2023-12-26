#include "LOG.h"

void LOG::WARNING(const std::string& Value){
    LOGDATA += "[WARNING] " + Value + "\n";
}

void LOG::INFO(const std::string& Value){
    LOGDATA += "[INFO] " + Value + "\n";
}

void LOG::MESSAGE(const std::string& Value){
    LOGDATA += "[MESSAGE] " + Value + "\n";
}

std::string LOG::GetLog() { return LOGDATA; };