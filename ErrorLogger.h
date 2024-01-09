#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <format>
#include <string>
class ErrorLogger
{
    static std::ofstream logFile;
    static std::string getCurrentTimestamp();
public:
    static void init(const char* logpath);

	static void log(const std::string& errorMessage);
    static void shutdown() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

