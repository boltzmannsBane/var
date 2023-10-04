#include <spdlog/spdlog.h>
#include "startup/startup.h"
#include "telemetry/telemetry.h"

int main() {
  initLogger();
  spdlog::info("Server started on {}", "127.0.0.1:8080");
  run();
}
