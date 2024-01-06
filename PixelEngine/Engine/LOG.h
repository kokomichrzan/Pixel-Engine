#pragma once
#include <vector>
#include <string>
#include <utility>
#include "ImGui/imgui.h"

class LOG
{
public: 
    static std::vector<std::pair<ImVec4, std::string>> LogData;
    static bool ScrollDown;
    void WARNING(const std::string& Value);
    void MESSAGE(const std::string& Value);
    void INFO(const std::string& Value);

};