#include "Logger.h"
#include <thread>
#include <chrono>

int main() {
    Logger logger;

    for (int i = 0; i < 10; ++i) {
        logger.logMessage("Log entry " + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return 0;
}
