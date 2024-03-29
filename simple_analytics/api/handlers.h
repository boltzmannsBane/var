#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

#include "utils.h"
#include "wrappers/spdlog/spdlog_wrapper.h"


void root_callback(struct evhttp_request *req, void *arg) {
    char* req_id = generate_unique_id();

    log_start(req_id, "hello_world", get_current_timestamp(), "caller_info");

    struct evbuffer *buf = evbuffer_new();
    if (!buf) {
        puts("Failed to create response buffer.");
        return;
    }

    if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
        evbuffer_add_printf(buf, "Only GET method is allowed!");
        // log_error(sprintf("RequestID: %s, Status: Error, Code: %d, Message: %s, Time: %s",
        //        req_id, 500, "error_message", get_current_timestamp()));
        evhttp_send_reply(req, 405, "Method Not Allowed", buf);
    } else {
        evbuffer_add_printf(buf, "Hello, World!");
        log_success(req_id, HTTP_OK, "success", get_current_timestamp());
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
    }

    evbuffer_free(buf);
}
