gcc -I./deps/libevent/include/ -L./deps/libevent/.libs/ -levent -levent_core -levent_extra -o server server.c

# g++ -o test test.cpp -I/deps/gtest/include/ -L/deps/gtest/lib/ -lgtest -lgtest_main -lgmock -pthread -levent -I/deps/libevent/include/ -L/deps/libevent/lib/
