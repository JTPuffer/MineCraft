#include "ErrorLogger.h"
std::ofstream ErrorLogger::logFile;

void ErrorLogger::init(const char* logpath)
{
	logFile.open(logpath, std::ios::out);
	if (!logFile.is_open()) {
		std::cerr << "Error: Unable to open log file: " << logpath << std::endl;
	}
}

void ErrorLogger::log(const std::string& errorMessage)
{
    std::string timestamp = getCurrentTimestamp();
    logFile << "[" << timestamp << "] ERROR: " << errorMessage << std::endl;
    std::cerr << "[" << timestamp << "] ERROR: " << errorMessage << std::endl;
}
std::string ErrorLogger::getCurrentTimestamp() {
    time_t now = time(0);
    struct tm ltm;

#ifdef _MSC_VER // Check if using Microsoft Visual C++
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ltm);

    return std::string(timestamp);
}