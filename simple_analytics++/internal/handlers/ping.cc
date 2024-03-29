#include <event2/http.h>
#include <event2/buffer.h>
#include <telemetry/telemetry.h>
#include <utils/utils.h>

using namespace std;

namespace handlers {

void ping(struct evhttp_request *req, void *arg) 
{

  evhttp_cmd_type method = evhttp_request_get_command(req);
  string reqId = generate_unique_id();
  string callerId = "randomCallerId";
  if (method == EVHTTP_REQ_GET) {
    telemetry::log_start(reqId, "GET /ping", callerId);
    struct evbuffer *evb = evbuffer_new();
    evbuffer_add_printf(evb, "All Good");
    evhttp_send_reply(req, HTTP_OK, "OK", evb);
    evbuffer_free(evb);
    telemetry::log_success(reqId, HTTP_OK,  "OK");
  } 

  // else if (method == EVHTTP_REQ_POST) {
  //   size_t len;
  //   char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
  //   len = EVBUFFER_LENGTH(req->input_buffer);
  //   post_data[len] = '\0';
  //
  //   struct evbuffer *evb = evbuffer_new();
  //   evbuffer_add_printf(evb, "You've sent: %s", post_data);
  //   evhttp_send_reply(req, HTTP_OK, "OK", evb);
  //   evbuffer_free(evb);
  //
  // } 

  else {
    evhttp_send_error(req, HTTP_BADMETHOD, NULL);
    telemetry::log_error(reqId, HTTP_BADMETHOD, "Bad Method", "Operation doesn't exists");
  }
}

}
