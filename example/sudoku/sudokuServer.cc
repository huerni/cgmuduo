#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>
#include <cgmuduo/Buffer.h>

#include "sudoku.h"

#include <string>
#include <functional>

using std::string;

const int kCells = 81;

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp) {
    size_t len = buf->readableBytes();
    while (len >= kCells + 2)
    {
        const char* crlf = buf->findCRLF();
        if(crlf) {
            string request(buf->peek(), crlf);
            string id;
            buf->retrieve(sizeof crlf);
            string::iterator colon = std::find(request.begin(), request.end(), ':');
            if(colon != request.end()) {
                id.assign(request.begin(), colon);
                request.erase(request.begin(), colon+1);
            }
            if(request.size() == implicit_cast<size_t>(kCells)) {
                string result = solveSudoku(request);
                if(id.empty()) {
                    conn->send(result+"\r\n");
                }
                else {
                    conn->send(id + ":" + result + "\r\n");
                }
            }
            else {
                conn->send("Bad Request!\r\n");
                conn->shutdown();
            }
        }
        else {
            break;
        }
    }
}


int main(){
    EventLoop loop;
    InetAddress addr(8001);
    
    return 0;
}