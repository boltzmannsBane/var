#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Handler : public HttpController<Handler> {
public:
    METHOD_LIST_BEGIN

    // Declare your endpoints here
    ADD_METHOD_TO(Handler::handleHello, "/api/hello", Get);
    ADD_METHOD_TO(Handler::handleStatus, "/api/status", Get);
    ADD_METHOD_TO(Handler::handleName, "/api/name", Post);
    ADD_METHOD_TO(Handler::handleData, "/api/data", Post);

    METHOD_LIST_END

    void handleHello(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback);

    void handleStatus(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback);

    void handleName(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);

    void handleData(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
};

