#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"
#include "spdlog_wrapper.h"

extern "C" {

    void log_start(char* req_id, char* operation, char* timestamp, char* caller_uid) {
        spdlog::info("RequestID: {}, Operation: {}, Time: {}, Caller: {}",
         req_id, operation, timestamp, caller_uid);
    }

    void log_error(const char* msg) {
        spdlog::error(msg);
    }

    void init_logger() {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] %v");
        spdlog::set_level(spdlog::level::info);
    }
}
