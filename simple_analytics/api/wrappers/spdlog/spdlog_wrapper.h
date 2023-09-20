#ifndef SPDLOG_WRAPPER_H
#define SPDLOG_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void log_start(char* req_id, char* operation, char* timestamp, char* caller_uid);
void log_error(const char* msg);
void init_logger();

#ifdef __cplusplus
}
#endif

#endif // SPDLOG_WRAPPER_H
