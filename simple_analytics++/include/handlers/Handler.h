#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Handler : public drogon::HttpController<Handler> {
public:
    METHOD_LIST_BEGIN

    // Declare your endpoints here
    ADD_METHOD_TO(Handler::handleHello, "/api/hello", Get);
    ADD_METHOD_TO(Handler::handleStatus, "/api/status", Get);
    ADD_METHOD_TO(Handler::handleName, "/api/name", Post);
    ADD_METHOD_TO(Handler::handleData, "/api/data", Post);

    METHOD_LIST_END

    void handleHello(const drogon::HttpRequestPtr &req,
                     std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void handleStatus(const drogon::HttpRequestPtr &req,
                      std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void handleName(const drogon::HttpRequestPtr &req,
                    std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void handleData(const drogon::HttpRequestPtr &req,
                    std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};

