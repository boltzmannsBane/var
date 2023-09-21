#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"
#include "spdlog_wrapper.h"

extern "C" {
    void log_start(char* req_id, char* operation, char* timestamp, char* caller_uid) {
        spdlog::info("RequestID: {}, Operation: {}, Time: {}, Caller: {}",
         req_id, operation, timestamp, caller_uid);
    }

    // log_info("RequestID: %s, Code: %d, Status: %s, Time: %s", req_id, HTTP_OK, "Success", get_current_timestamp());
    void log_success(char* req_id, int code,  char* status, char* timestamp) {
        spdlog::info("RequestID: {}, Code: {}, Status: {}, Time: {}",
         req_id, code, status, timestamp);
    }

    void log_error(const char* msg) {
        spdlog::error(msg);
    }

    void init_logger() {
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
        spdlog::set_level(spdlog::level::info);
    }
}
