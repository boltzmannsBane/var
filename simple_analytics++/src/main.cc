#include <spdlog/spdlog.h>

void initLogger() {
    // Create color multi threaded logger
    spdlog::set_level(spdlog::level::info);  // Set global log level to info
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
}

int main() {
    initLogger();
    // LOG_INFO << "Server running on 127.0.0.1:8848";
    // app().addListener("127.0.0.1", 8848).run();
}
