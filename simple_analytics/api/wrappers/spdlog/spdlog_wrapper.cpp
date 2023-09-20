#include "spdlog/spdlog.h"
#include "spdlog_wrapper.h"

extern "C" {
    void log_info(const char* msg) {
        spdlog::info(msg);
    }

    void log_error(const char* msg) {
        spdlog::error(msg);
    }

    void init_logger() {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] %v");
        spdlog::set_level(spdlog::level::info);
    }
}

