#include "handlers/Handler.h"

void Handler::handleHello(const drogon::HttpRequestPtr &req,
                                    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("Hello from /api/hello endpoint!");
    callback(resp);
}

void Handler::handleStatus(const drogon::HttpRequestPtr &req,
                                     std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("Server is up and running!");
    callback(resp);
}

void Handler::handleName(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();

    if (json && json->isMember("name")) {
        auto name = (*json)["name"].asString();
        resp->setBody("Hello, " + name + " from /api/name endpoint!");
    } else {
        resp->setBody("Name not provided!");
    }

    callback(resp);
}

void Handler::handleData(const drogon::HttpRequestPtr &req,
                                   std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();

    if (json) {
        resp->setBody("Data received: " + json->toStyledString());
    } else {
        resp->setBody("No data provided!");
    }

    callback(resp);
}
