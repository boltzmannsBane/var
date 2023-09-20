#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"
#include "spdlog_wrapper.h"

extern "C" {
  void log_info(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);

        // Estimate the required buffer size
        va_list args_copy;
        va_copy(args_copy, args);
        int required_size = vsnprintf(nullptr, 0, fmt, args_copy) + 1;
        va_end(args_copy);

        // Create a buffer of the required size
        std::vector<char> buffer(required_size);

        // Format the string into the buffer
        vsnprintf(buffer.data(), required_size, fmt, args);

        // Log the message
        spdlog::info(buffer.data());

        va_end(args);
    }

    void log_error(const char* msg) {
        spdlog::error(msg);
    }

    void init_logger() {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] %v");
        spdlog::set_level(spdlog::level::info);
    }
}
