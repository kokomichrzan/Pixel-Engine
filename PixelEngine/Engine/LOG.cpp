#include "LOG.h"

void LOG::WARNING(std::string Value){
    LOGDATA += "[WARNING] " + Value + "\n";
}

void LOG::INFO(std::string Value){
    LOGDATA += "[INFO] " + Value + "\n";
}

void LOG::MESSAGE(std::string Value){
    LOGDATA += "[MESSAGE] " + Value + "\n";
}

std::string LOG::GETLOG(){
    return LOGDATA;
}