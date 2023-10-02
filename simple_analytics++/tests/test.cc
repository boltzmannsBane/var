// #include <gtest/gtest.h>
// #include <drogon/drogon.h>
// #include <future>
// #include <thread>
// #include "handlers/Handler.h"
//
// using namespace drogon;
//
// // Define a coroutine function that sends an HTTP request using Drogon
// Task<> api_test() {
//     auto client = HttpClient::newHttpClient("http://localhost:8848");
//     auto req = HttpRequest::newHttpRequest();
//     req->setPath("/api/v1/hello");
//
//     auto resp = co_await client->sendRequestCoro(req);
//     EXPECT_NE(resp, nullptr); // Use EXPECT_* macros from gtest
//     EXPECT_EQ(resp->getStatusCode(), k200OK);
//     // EXPECT_EQ(resp->contentType(), CT_APPLICATION_JSON);
// }
//
// TEST(RemoteAPITestCoro, BasicTest) {
//     sync_wait(api_test());
// }
//
// int main(int argc, char *argv[]) {
//     std::promise<void> p1;
//     std::future<void> f1 = p1.get_future();
//
//     // Initialize Google Test
//     ::testing::InitGoogleTest(&argc, argv);
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
//     int status = RUN_ALL_TESTS();
//
//     // Ask the event loop to shutdown and wait
//     app().getLoop()->queueInLoop([]() { app().quit(); });
//     thr.join();
//
//     return status;
// }
