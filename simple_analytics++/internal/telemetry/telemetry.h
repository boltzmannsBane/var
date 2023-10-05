#pragma once

#include <string> 
using namespace std;

namespace telemetry {
  void initLogger();
  void log_server_start(string port);
  void log_start(string req_id, string operation, string caller_uid);
  void log_success(string req_id, int code,  string status);
  void log_error(std::string req_id, int code,  string status, string msg);
}


