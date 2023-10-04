add_library(startup)
target_sources(startup PRIVATE startup/startup.cc)
target_link_libraries(startup PRIVATE event handlers)

add_library(handlers)
target_sources(handlers PRIVATE handlers/ping.cc)
target_link_libraries(handlers PRIVATE event telemetry)

add_library(telemetry)
target_sources(telemetry PRIVATE telemetry/telemetry.cc)
target_link_libraries(telemetry PRIVATE spdlog)

add_library(configuration)
target_sources(configuration PRIVATE configuration/configuration.cc)
target_link_libraries(configuration PRIVATE event handlers)
