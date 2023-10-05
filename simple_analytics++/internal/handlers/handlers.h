#pragma once

#include <event2/http.h>
#include <event2/buffer.h>

namespace handlers {
  void ping(struct evhttp_request *req, void *arg);
}
