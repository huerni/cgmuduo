#include <cgmuduo/EventLoop.h>
#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>
#include <cgmuduo/Timestamp.h>

#include <string>
#include <map>

using std::string;

using UserMap = std::map<string, string>;
UserMap users;

string getUser(const string& user) {
    string result = "No such user";
    UserMap::iterator it = users.find(user);
    if(it != users.end()) {
        result = it->second;
    }
    return result;
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime) {
    const char* crlf = buf->findCRLF();
    if(crlf) {
        string user(buf->peek(), crlf);
        conn->send(getUser(user) + "\r\n");
        buf->retrieve((size_t)sizeof crlf);
        conn->shutdown();
    }
}

int main() {
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1079), "finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();

    return 0;
}