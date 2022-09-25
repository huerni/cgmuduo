#include "cgmuduo/TcpServer.h"
#include "cgmuduo/Timestamp.h"
#include "cgmuduo/Logger.h"
#include "sudoku.h"

#include <unistd.h>
#include <utility>

class SudokuServer{
public:
    SudokuServer(EventLoop* loop, const InetAddress& listenAddr)
    : server_(loop, listenAddr, "SudokuServer")
    , startTime_(Timestamp::now()) {
        server_.setConnectionCallback(
            std::bind(&SudokuServer::onConnection, this, std::placeholders::_1)
        );
        server_.setMessageCallback(
            std::bind(&SudokuServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );
    }

    void start() {
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr& conn) {
        if(conn->connected()) {
            LOG_INFO("connection up : %s", conn->peerAddr().toIpPort().c_str());
        }
        else {
            LOG_INFO("connection down : %s", conn->peerAddr().toIpPort().c_str());
        }
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp) {
        size_t len = buf->readableBytes();
        while(len >= kCells + 2) {
            const char* crlf = buf->findCRLF();
            if(crlf) {
                string request(buf->peek(), crlf);
                buf->retrieve(sizeof crlf);
                len = buf->readableBytes();
                if(!processRequest(conn, request)) {
                    conn->send("Bad Request!\r\n");
                    conn->shutdown();
                    break;
                }                
            }
            else if(len > 100) {
                conn->send("Id too long!\r\n");
                conn->shutdown();
                break;
            }
            else {
                break;
            }
        }
    }

    bool processRequest(const TcpConnectionPtr& conn, const string& request) {
        string id;
        string puzzle;
        bool goodRequest = true;

        string::const_iterator colon = std::find(request.begin(), request.end(), ':');
        if(colon != request.end()) {
            id.assign(request.begin(), colon);
            puzzle.assign(colon+1, request.end());
        }
        else {
            puzzle = request;
        }

        if(puzzle.size() == static_cast<size_t>(kCells)) {
            string result = solveSudoku(puzzle);
            if(id.empty()) {
                conn->send(result + "\r\n");
            }
            else {
                conn->send(id + ":" + result + "\r\n");
            }
        }
        else {
            goodRequest = false;
        }
        return goodRequest;
    }

    TcpServer server_;
    Timestamp startTime_;
};


int main() {
    LOG_INFO("pid = %d, tid = %d", getpid(), CurrentThread::tid());

    EventLoop loop;
    InetAddress listenAddr(9981);
    SudokuServer server(&loop, listenAddr);

    server.start();
    loop.loop();
    
    return 0;
}