#ifndef PING_HANDLERS_H
#define PING_HANDLERS_H

#include <event2/http.h>
#include <event2/buffer.h>

void ping(struct evhttp_request *req, void *arg) {

  evhttp_cmd_type method = evhttp_request_get_command(req);
  if (method == EVHTTP_REQ_GET) {
    struct evbuffer *evb = evbuffer_new();
    evbuffer_add_printf(evb, "All Good");
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
    evbuffer_free(evb);

  } else if (method == EVHTTP_REQ_POST) {
    size_t len;
    char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
    len = EVBUFFER_LENGTH(req->input_buffer);
    post_data[len] = '\0';

    struct evbuffer *evb = evbuffer_new();
    evbuffer_add_printf(evb, "You've sent: %s", post_data);
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
    evbuffer_free(evb);

  } else {
      evhttp_send_error(req, HTTP_BADMETHOD, NULL);
  }
}

#endif // PING_HANDLERS_H
