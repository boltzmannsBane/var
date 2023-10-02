#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"
#include <sys/time.h>

#include "Handler.h"

using namespace drogon;
using namespace std;

#define TIMESTAMP_SIZE 100

char* get_current_timestamp() {
    static char timestamp[TIMESTAMP_SIZE];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp)-1, "%Y-%m-%d %H:%M:%S", t);
    return timestamp;
}

#define UNIQUE_ID_SIZE 50

char* generate_unique_id() {
    static char unique_id[UNIQUE_ID_SIZE];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long timestamp_micro = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
    int random_value = rand(); // Use a better random generator for more entropy if needed
    snprintf(unique_id, sizeof(unique_id), "%lld-%d", timestamp_micro, random_value);
    return unique_id;
}

void Handler::handleHello(const HttpRequestPtr &req,
                                    std::function<void(const HttpResponsePtr &)> &&callback) {
    
    string method = req->getMethodString();
    string path = req->path();
    string req_id = generate_unique_id();
    string start_time = get_current_timestamp();

    spdlog::info("{} {} {} {} {}", method, path, "START", req_id, "Some Message");

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Hello from /api/v1/hello endpoint!");
    callback(resp);
    spdlog::info("{} {} {} {} {} {}", method, path, "END", req_id, 200, "SUCCESS");
}

// void Handler::handleStatus(const HttpRequestPtr &req,
//                                      std::function<void(const HttpResponsePtr &)> &&callback) {
//     auto resp = HttpResponse::newHttpResponse();
//     resp->setBody("Server is up and running!");
//     callback(resp);
// }
//
// void Handler::handleName(const HttpRequestPtr &req,
//                                    std::function<void(const HttpResponsePtr &)> &&callback) {
//     auto resp = HttpResponse::newHttpResponse();
//     auto json = req->getJsonObject();
//
//     if (json && json->isMember("name")) {
//         auto name = (*json)["name"].asString();
//         resp->setBody("Hello, " + name + " from /api/name endpoint!");
//     } else {
//         resp->setBody("Name not provided!");
//     }
//
//     callback(resp);
// }
//
// void Handler::handleData(const HttpRequestPtr &req,
//                                    std::function<void(const HttpResponsePtr &)> &&callback) {
//     auto resp = HttpResponse::newHttpResponse();
//     auto json = req->getJsonObject();
//
//     if (json) {
//         resp->setBody("Data received: " + json->toStyledString());
//     } else {
//         resp->setBody("No data provided!");
//     }
//
//     callback(resp);
// }
