# Compile the spdlog wrapper
# g++ -I./deps/spdlog/include -c ./wrappers/spdlog/spdlog_wrapper.cpp -o spdlog_wrapper.o
g++ -std=c++11 -I./deps/spdlog/include -c ./wrappers/spdlog/spdlog_wrapper.cpp -o spdlog_wrapper.o

# Compile the server.c code
gcc -I./deps/libevent/include/ -c server.c -o server.o

# Link everything together
gcc server.o spdlog_wrapper.o -L./deps/libevent/.libs/ -levent -levent_core -levent_extra -lstdc++ -o server
