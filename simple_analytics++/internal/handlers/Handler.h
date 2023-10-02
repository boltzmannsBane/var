#pragma once

#include <drogon/HttpController.h>


class Handler : public drogon::HttpController<Handler> {
public:
    METHOD_LIST_BEGIN

    // Declare your endpoints here
    ADD_METHOD_TO(Handler::handleHello, "/api/v1/hello", drogon::Get);
    // ADD_METHOD_TO(Handler::handleStatus, "/api/status", Get);
    // ADD_METHOD_TO(Handler::handleName, "/api/name", Post);
    // ADD_METHOD_TO(Handler::handleData, "/api/data", Post);

    METHOD_LIST_END

    void handleHello(const drogon::HttpRequestPtr &req,
                     std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    // void handleStatus(const HttpRequestPtr &req,
    //                   std::function<void(const HttpResponsePtr &)> &&callback);
    //
    // void handleName(const HttpRequestPtr &req,
    //                 std::function<void(const HttpResponsePtr &)> &&callback);
    //
    // void handleData(const HttpRequestPtr &req,
    //                 std::function<void(const HttpResponsePtr &)> &&callback);
};

