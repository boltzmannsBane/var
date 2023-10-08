#include <string> 
#include <spdlog/spdlog.h>

using namespace std;

namespace telemetry {

void initLogger() 
{
    spdlog::set_level(spdlog::level::info);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
}

void log_server_start(string port) 
{
    spdlog::info("Server started on 127.0.0.1:{}", port);
}

void log_start(string req_id, string operation, string caller_uid) 
{
    spdlog::info("RequestID: {}, Operation: {}, Caller: {}",
     req_id, operation, caller_uid);
}

void log_success(string req_id, int code,  string status) 
{
    spdlog::info("RequestID: {}, Code: {}, Status: {}",
     req_id, code, status);
}

void log_error(std::string req_id, int code,  string status, string msg) 
{
    spdlog::error("RequestID: {}, Code: {}, Status: {}, Message: {}",
     req_id, code, status, msg);
}

}
