gcc server.c -o server -levent -levent_core -levent_extra

# g++ -o test test.cpp -lgtest -lgtest_main -pthread

g++ -o test test.cpp -lgtest -lgtest_main -pthread -levent
