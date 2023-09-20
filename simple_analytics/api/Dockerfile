FROM debian:bullseye-slim

# Update and install build tools
RUN apt-get update && \
    apt-get install -y googletest build-essential libevent-dev

WORKDIR /app
