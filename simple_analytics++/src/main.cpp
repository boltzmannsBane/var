#include <drogon/drogon.h>
using namespace drogon;

int main() {
    LOG_INFO << "Server running on 127.0.0.1:8848";
    app().addListener("127.0.0.1", 8848).run();
}
