FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y libgtest-dev build-essential libevent-dev git cmake && \
    cd deps && \
    git clone https://github.com/google/googletest.git && \
    cd googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

WORKDIR /app
