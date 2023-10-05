#include "startup/startup.h"
#include "telemetry/telemetry.h"

int main() {
  telemetry::initLogger();
  telemetry::log_server_start("8080");
  startup::run();
}
