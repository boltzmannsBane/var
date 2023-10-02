#include <doctest/doctest.h>
#include <drogon/drogon.h>
#include <future>
#include <thread>
#include "handlers/Handler.h"

using namespace drogon;

// Define a coroutine function that sends an HTTP request using Drogon
Task<> api_test() {
    auto client = HttpClient::newHttpClient("http://localhost:8848");
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/api/v1/hello");

    auto resp = co_await client->sendRequestCoro(req);
    DOCTEST_CHECK(resp != nullptr); // Use DOCTEST_CHECK instead of EXPECT_*
    DOCTEST_CHECK(resp->getStatusCode() == k200OK);
    // DOCTEST_CHECK(resp->contentType() == CT_APPLICATION_JSON);
}

DOCTEST_TEST_CASE("RemoteAPITestCoro - BasicTest") {
    sync_wait(api_test());
}

int main(int argc, char *argv[]) {
    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Initialize doctest
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Initialize your drogon app, set routes, etc.
        app().addListener("127.0.0.1", 8848);

        // Queue the promise to be fulfilled after starting the loop
        app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
        app().run();
    });

    // The future is only satisfied after the event loop started
    f1.get();
    int status = context.run();

    // Ask the event loop to shutdown and wait
    app().getLoop()->queueInLoop([]() { app().quit(); });
    thr.join();

    return status;
}
