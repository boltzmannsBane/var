#ifndef SPDLOG_WRAPPER_H
#define SPDLOG_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void log_info(const char* msg, ...);
void log_error(const char* msg);
void init_logger();

#ifdef __cplusplus
}
#endif

#endif // SPDLOG_WRAPPER_H
