#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>
#include <drogon/drogon.h>
#include <future>
#include <thread>

using namespace drogon;

DROGON_TEST(RemoteAPITestCoro)
{
    auto api_test = [TEST_CTX]() -> Task<> {
        auto client = HttpClient::newHttpClient("http://localhost:8848");
        auto req = HttpRequest::newHttpRequest();
        req->setPath("/api/v1/hello");

        auto resp = co_await client->sendRequestCoro(req);
        CO_REQUIRE(resp != nullptr);
        CHECK(resp->getStatusCode() == k200OK);
        CHECK(resp->contentType() == CT_APPLICATION_JSON);
    };

    sync_wait(api_test());
}

int main(int argc, char *argv[])
{
    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Start the main loop on another thread
    // std::thread thr([&]() {
        // Initialize your drogon app, set routes, etc.
        app().addListener("127.0.0.1", 8848).run();

        // Queue the promise to be fulfilled after starting the loop
        // app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
        // app().run();
    // });

    // The future is only satisfied after the event loop started
    // f1.get();
    // int status = test::run(argc, argv);
    //
    // // Ask the event loop to shutdown and wait
    // app().getLoop()->queueInLoop([]() { app().quit(); });
    // thr.join();
    //
    // return status;
}
