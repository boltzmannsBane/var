#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <drogon/drogon.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
// other libevent headers as needed...
#include <future>
#include <thread>
#include "handlers/Handler.h"

using namespace drogon;

const int PORT = 8848;

// Define a coroutine function that sends an HTTP request using Drogon
Task<> api_test() {
    auto client = HttpClient::newHttpClient("http://127.0.0.1:{}", PORT);
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/api/v1/hello");
    LOG_INFO << "prepping to make the request";

    try {
        // Set a timeout for the request
        req->setTimeOut(5.0);  // Set a timeout of 5 seconds
        
        auto resp = co_await client->sendRequestCoro(req);

        // Log details about the response
        LOG_INFO << "Response received:";
        LOG_INFO << "    Status code: " << resp->getStatusCode();
        LOG_INFO << "    Body: " << resp->getBody();
    }
    catch (const std::exception &e) {
        std::cerr << "Caught general exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    LOG_INFO << "request finished or timed out";
    // CHECK(resp != nullptr); 
    // CHECK(resp->getStatusCode() == k200OK);
    // CHECK(resp->contentType() == CT_APPLICATION_JSON);
}

TEST_CASE("RemoteAPITestCoro - BasicTest") {
    sync_wait(api_test());
}

int main(int argc, char *argv[]) {
    // Initialize doctest
    doctest::Context context;

    // overrides
    context.setOption("no-breaks", true);  // don't break in the debugger when assertions fail
    context.applyCommandLine(argc, argv);

    // Run the test cases
    int status = context.run();

    // Ask the event loop to shutdown and wait
    // app().quit();
    // thr.join();

    return status;
}
