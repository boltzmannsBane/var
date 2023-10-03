#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <drogon/drogon.h>
#include <future>
#include <thread>

using namespace drogon;

Task<> api_test() {
    auto client = HttpClient::newHttpClient("http://localhost:8848");
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/api/v1/hello");

    auto resp = co_await client->sendRequestCoro(req);
    CHECK(resp != nullptr); 
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

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Initialize your drogon app, set routes, etc.
        app().addListener("127.0.0.1", 8848);
        app().run();
    });

    // Give the server some time to start up before running the tests
    // Adjust the sleep duration according to your server's startup time
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Run the test cases
    int status = context.run();

    // Ask the event loop to shutdown and wait
    app().quit();
    thr.join();

    return status;
}
