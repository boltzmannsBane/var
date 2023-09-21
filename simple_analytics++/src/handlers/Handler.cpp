#include "handlers/Handler.h"

using namespace drogon;

void Handler::handleHello(const HttpRequestPtr &req,
                                    std::function<void(const HttpResponsePtr &)> &&callback) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Hello from /api/hello endpoint!");
    callback(resp);
}

void Handler::handleStatus(const HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Server is up and running!");
    callback(resp);
}

void Handler::handleName(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback) {
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();

    if (json && json->isMember("name")) {
        auto name = (*json)["name"].asString();
        resp->setBody("Hello, " + name + " from /api/name endpoint!");
    } else {
        resp->setBody("Name not provided!");
    }

    callback(resp);
}

void Handler::handleData(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback) {
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();

    if (json) {
        resp->setBody("Data received: " + json->toStyledString());
    } else {
        resp->setBody("No data provided!");
    }

    callback(resp);
}
