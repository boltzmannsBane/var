FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y curl build-essential git cmake

RUN cd deps && \
    curl -LO https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz && \
    tar xzf googletest-1.14.0.tar.gz && \
    cd googletest-1.14.0 && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

RUN cd deps && \
    curl -LO https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz && \
    tar xzf libevent-2.1.12-stable.tar.gz && \
    cd libevent-2.1.12-stable && \
    ./configure && \
    make


WORKDIR /app
