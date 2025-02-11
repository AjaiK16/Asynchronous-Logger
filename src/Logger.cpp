#include "Logger.h"

Logger::Logger() {
    logThread = std::thread(&Logger::flushLogs, this);
}

Logger::~Logger() {
    threadRunning = false;
    if (logThread.joinable())
        logThread.join();
}

void Logger::logMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutexInsert);
    std::ostringstream* activeBuffer = switchBuffer ? &buffer1 : &buffer2;
    *activeBuffer << getCurrentTimestamp() << " " << message << std::endl;
}

void Logger::flushLogs() {
    while (threadRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Non-blocking delay

        std::lock_guard<std::mutex> lock(mutexFlush);
        std::ostringstream* activeBuffer = switchBuffer ? &buffer1 : &buffer2;
        std::ostringstream* idleBuffer = switchBuffer ? &buffer2 : &buffer1;
        switchBuffer = !switchBuffer;  // Swap buffers

        if (!idleBuffer->str().empty()) {
            std::ofstream logFile("log_output.txt", std::ios::app);
            logFile << idleBuffer->str();
            idleBuffer->str("");  // Clear buffer
            logFile.close();
        }
    }
}

// Function to get timestamp
std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", localtime(&nowTime));
    return std::string(buffer);
}
