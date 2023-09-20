#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

#include "handlers.h"

int main() {
    struct event_base *base = event_base_new();
    struct evhttp *http = evhttp_new(base);
    evhttp_bind_socket(http, "0.0.0.0", 8080);
    openlog("cserv", LOG_PID | LOG_CONS, LOG_USER);

    // Define routes
    evhttp_set_cb(http, "/", root_callback, NULL);
    // evhttp_set_cb(http, "/hello", hello_callback, NULL);

    printf("Server running on http://127.0.0.1:8080\n");
    event_base_dispatch(base);
    return 0;
}
