#pragma once

#include <spdlog/spdlog.h>
#include <event2/http.h>
#include <event2/buffer.h>

void initLogger();
void run();
