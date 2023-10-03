#include <spdlog/spdlog.h>

void initLogger() {
    // Create color multi threaded logger
    spdlog::set_level(spdlog::level::info);  // Set global log level to info
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
}
