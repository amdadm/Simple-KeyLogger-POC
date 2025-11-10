#pragma once
#include <shlobj.h>
#include <filesystem>
#include <mutex>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include "config.h"

namespace output {
    void save() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(config::chrono::time));

            wchar_t documentsPath[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, 0, documentsPath))) {
                std::wstring folderPath = std::wstring(documentsPath) + L"\\VisionClass\\Admin\\Resources\\";
                std::filesystem::create_directories(folderPath);

                std::wstring filePath = folderPath + L"\\output.txt";

                std::wofstream file(filePath, std::ios::trunc);
                file.imbue(std::locale("es_ES.UTF-8"));

                if (file.is_open()) {
                    file << config::g_text;
                    file.close();
                }
            }
        }
    }
}