#include "LOG.h"

//Add Log
void LOG::WARNING(const std::string& Value){
    LogData += "[WARNING] " + Value + "\n";
    ScrollDown = true;

}

void LOG::INFO(const std::string& Value){
    LogData += "[INFO] " + Value + "\n";
    ScrollDown = true;

}

void LOG::MESSAGE(const std::string& Value){
    LogData += "[MESSAGE] " + Value + "\n";
    ScrollDown = true;

}

//GetLog
const std::string& LOG::GetLog() {return LogData;}

bool LOG::CheckIfScrollDown(){
    bool CurrentScrollDownState = ScrollDown;
    ScrollDown = false;
    return CurrentScrollDownState;

}