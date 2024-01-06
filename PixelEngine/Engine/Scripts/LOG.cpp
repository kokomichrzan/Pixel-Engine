#include <pch.h>
#include "LOG.h"

std::vector<std::pair<ImVec4, std::string>> LOG::LogData;
bool LOG::ScrollDown;

void LOG::WARNING(const std::string& Value){
    LogData.emplace_back(std::make_pair(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[WARNING] " + Value));
    LOG::ScrollDown = true;
}

void LOG::MESSAGE(const std::string& Value){
    LogData.emplace_back(std::make_pair(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "[MESSAGE] " + Value));
    LOG::ScrollDown = true;
}

void LOG::INFO(const std::string& Value) {
    LogData.emplace_back(std::make_pair(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "[INFO] " + Value));
    LOG::ScrollDown = true;
}

