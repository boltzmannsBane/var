#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/time.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

#define TIMESTAMP_SIZE 100

char* get_current_timestamp() {
    static char timestamp[TIMESTAMP_SIZE];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp)-1, "%Y-%m-%d %H:%M:%S", t);
    return timestamp;
}

#define UNIQUE_ID_SIZE 50

char* generate_unique_id() {
    static char unique_id[UNIQUE_ID_SIZE];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long timestamp_micro = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
    int random_value = rand(); // Use a better random generator for more entropy if needed
    snprintf(unique_id, sizeof(unique_id), "%lld-%d", timestamp_micro, random_value);
    return unique_id;
}

void root_callback(struct evhttp_request *req, void *arg) {
    char* req_id = generate_unique_id();

    syslog(LOG_INFO, "RequestID: %s, Operation: %s, Time: %s, Caller: %s",
       req_id, "hello_world", get_current_timestamp(), "caller_info");

    struct evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer.");
        return;
    }

    if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
        evbuffer_add_printf(buf, "Only GET method is allowed!");
        syslog(LOG_ERR, "RequestID: %s, Status: Error, Code: %d, Message: %s, Time: %s",
               req_id, error_code, "error_message", get_current_timestamp());
        evhttp_send_reply(req, 405, "Method Not Allowed", buf);
    } else {
        evbuffer_add_printf(buf, "Hello, World!");
        syslog(LOG_INFO, "RequestID: %s, Code: %d, Status: %s, Time: %s", req_id, HTTP_OK, "Success", get_current_timestamp());
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
    }

    evbuffer_free(buf);
}

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
