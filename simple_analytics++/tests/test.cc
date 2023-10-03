#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/keyvalq_struct.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>

// Global variable to store HTTP response data
std::string http_response_data;
struct event_base *base; 

// Callback function to handle the HTTP request response
void http_request_done(struct evhttp_request *req, void *arg) {
    if (req == nullptr) {
        // Handle error
        std::cerr << "Request failed" << std::endl;
        return;
    }

    char buffer[256];
    int nread;
    while ((nread = evbuffer_remove(evhttp_request_get_input_buffer(req),
                                     buffer, sizeof(buffer)))
           > 0) {
        // Append the response data to the global variable
        http_response_data.append(buffer, nread);
    }

    // Notify the main thread that the response has been received
    auto* base = static_cast<struct event_base*>(arg);
    event_base_loopbreak(base);
}

void server_thread() {
    base = event_base_new();  // Set the global event_base
    struct evhttp *http = evhttp_new(base);

    evhttp_set_cb(http, "/api/v1/hello", [](struct evhttp_request *req, void *arg) {
        auto *buf = evbuffer_new();
        evbuffer_add_printf(buf, "Hello from /api/v1/hello endpoint!");
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
        evbuffer_free(buf);
    }, nullptr);

    evhttp_bind_socket(http, "127.0.0.1", 8848);
    event_base_dispatch(base);

    evhttp_free(http);
    event_base_free(base);
}

TEST_CASE("HTTP Request Test") {
    // Initialize libevent
    event_base *base = event_base_new();

    // Create an HTTP connection
    evhttp_connection *conn = evhttp_connection_base_new(base, nullptr, "127.0.0.1", 8848);

    // Create an HTTP request
    evhttp_request *req = evhttp_request_new(http_request_done, base);

    // Make an HTTP GET request
    evhttp_make_request(conn, req, EVHTTP_REQ_GET, "/api/v1/hello");

    // Dispatch events
    event_base_dispatch(base);

    // Clean up
    evhttp_connection_free(conn);
    event_base_free(base);

    // Check the HTTP response data
    CHECK(http_response_data == "Hello from /api/v1/hello endpoint!");
}

int main(int argc, char *argv[]) {
    std::thread serverThread(server_thread);
    int result = doctest::Context(argc, argv).run();
    event_base_loopbreak(base);  // Stop the event loop
    serverThread.join();
    return result;
}
