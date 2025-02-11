#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <ctime>

class Logger {
private:
    std::ostringstream buffer1, buffer2;
    std::mutex mutexInsert, mutexFlush;
    std::atomic<bool> switchBuffer{false};
    std::atomic<bool> threadRunning{true};
    std::thread logThread;

    void flushLogs();
    std::string getCurrentTimestamp(); // Function to add timestamps

public:
    Logger();
    ~Logger();

    void logMessage(const std::string& message);
};

#endif // LOGGER_H
