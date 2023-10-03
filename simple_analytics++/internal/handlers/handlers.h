#ifndef ROUTE_HANDLERS_H
#define ROUTE_HANDLERS_H

#include <event2/http.h>
#include <event2/buffer.h>

void get_handler(struct evhttp_request *req, void *arg) {
    struct evbuffer *evb = evbuffer_new();
    evbuffer_add_printf(evb, "Hello, World! This is a GET request.");
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
    evbuffer_free(evb);
}

void post_handler(struct evhttp_request *req, void *arg) {
    size_t len;
    char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
    len = EVBUFFER_LENGTH(req->input_buffer);
    post_data[len] = '\0';

    struct evbuffer *evb = evbuffer_new();
    evbuffer_add_printf(evb, "You've sent: %s", post_data);
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
    evbuffer_free(evb);
}

#endif // ROUTE_HANDLERS_H
