#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

void root_callback(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer.");
        return;
    }
    evbuffer_add_printf(buf, "Hello from root!");
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

void hello_callback(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer.");
        return;
    }

    if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
        evbuffer_add_printf(buf, "Only GET method is allowed!");
        evhttp_send_reply(req, 405, "Method Not Allowed", buf);
    } else {
        evbuffer_add_printf(buf, "Hello, World!");
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
    }

    evbuffer_free(buf);
}

void custom_callback(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer.");
        return;
    }
    evbuffer_add_printf(buf, "This is a custom route!");
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

int main() {
    struct event_base *base = event_base_new();
    struct evhttp *http = evhttp_new(base);
    evhttp_bind_socket(http, "0.0.0.0", 8080);

    // Define routes
    evhttp_set_cb(http, "/", root_callback, NULL);
    evhttp_set_cb(http, "/hello", hello_callback, NULL);
    evhttp_set_cb(http, "/custom", custom_callback, NULL);

    printf("Server running on http://127.0.0.1:8080\n");
    event_base_dispatch(base);
    return 0;
}
