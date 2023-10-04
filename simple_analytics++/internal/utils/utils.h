#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/time.h>
#include <stdbool.h>

// Define the error type
typedef struct {
    bool has_error;
    const char* message;
} Error;

// Define the generic result type
typedef struct {
    void* value;
    Error error;
} Result;

#define TIMESTAMP_SIZE 100

char* get_current_timestamp();
char* generate_unique_id();

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
