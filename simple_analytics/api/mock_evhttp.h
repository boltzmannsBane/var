#include <string.h>
#include <stdlib.h>

#ifndef MOCK_EVHTTP_H
#define MOCK_EVHTTP_H

struct evbuffer {
    char *data;
    size_t length;
};

struct evhttp_request {
    struct evbuffer *input_buffer;   // represents the request body
    struct evbuffer *output_buffer;  // represents the response body
    int response_code;               // stores the HTTP response code
    const char *uri;                 // the requested URI
    // Add any other attributes you might access in root_callback.
};

// Functions to help with testing
struct evbuffer *mock_evbuffer_new();
void mock_evbuffer_free(struct evbuffer *buffer);
void mock_evbuffer_add(struct evbuffer *buffer, const char *data, size_t datlen);

#endif // MOCK_EVHTTP_H

struct evbuffer *mock_evbuffer_new() {
    struct evbuffer *buffer = (struct evbuffer *)malloc(sizeof(struct evbuffer));
    buffer->data = NULL;
    buffer->length = 0;
    return buffer;
}

void mock_evbuffer_free(struct evbuffer *buffer) {
    if (buffer->data) {
        free(buffer->data);
    }
    free(buffer);
}

void mock_evbuffer_add(struct evbuffer *buffer, const char *data, size_t datlen) {
    buffer->data = (char *)realloc(buffer->data, buffer->length + datlen);
    memcpy(buffer->data + buffer->length, data, datlen);
    buffer->length += datlen;
}
