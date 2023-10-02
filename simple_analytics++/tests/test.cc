#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <drogon/drogon.h>
#include <future>
#include <thread>
#include "handlers/Handler.h"

using namespace drogon;

int factorial(int number) { return number > 1 ? factorial(number - 1) * number : 1; }

TEST_CASE("testing the factorial function") {
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

int main(int argc, char** argv) {
  doctest::Context context;
    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
    context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
    context.setOption("order-by", "name");            // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
    
    int client_stuff_return_code = 0;
    // your program - if the testing framework is integrated in your production code
    
    return res + client_stuff_return_code; //
}

// Define a coroutine function that sends an HTTP request using Drogon
Task<> api_test() {
    auto client = HttpClient::newHttpClient("http://localhost:8848");
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/api/v1/hello");

    auto resp = co_await client->sendRequestCoro(req);
    CHECK(resp != nullptr); 
    CHECK(resp->getStatusCode() == k200OK);
    CHECK(resp->contentType() == CT_APPLICATION_JSON);
}
//
TEST_CASE("RemoteAPITestCoro - BasicTest") {
    sync_wait(api_test());
}
//
// int main(int argc, char *argv[]) {
//     std::promise<void> p1;
//     std::future<void> f1 = p1.get_future();
//
//     // Initialize doctest
//     doctest::Context context;
//     context.applyCommandLine(argc, argv);
//
//     // Start the main loop on another thread
//     std::thread thr([&]() {
//         // Initialize your drogon app, set routes, etc.
//         app().addListener("127.0.0.1", 8848);
//
//         // Queue the promise to be fulfilled after starting the loop
//         app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
//         app().run();
//     });
//
//     // The future is only satisfied after the event loop started
//     f1.get();
//     int status = context.run();
//
//     // Ask the event loop to shutdown and wait
//     app().getLoop()->queueInLoop([]() { app().quit(); });
//     thr.join();
//
//     return status;
// }
