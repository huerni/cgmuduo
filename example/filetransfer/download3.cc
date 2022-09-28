#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>

#include <unistd.h>


void onHighWaterMark(const TcpConnectionPtr& conn, size_t len)
{
    LOG_INFO("HighWaterMark %d", len);
}

const int kBufSize = 64*1024;
const char* g_file = NULL;
typedef std::shared_ptr<FILE> FilePtr;

void onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO("FileServer - %s -> %s is %s", 
            conn->peerAddr().toIpPort().c_str(), 
            conn->localAddr().toIpPort().c_str(), 
            (conn->connected() ? "UP" : "DOWN")
    );

    if (conn->connected())
    {
        LOG_INFO("FileServer -Sending file %s to %s", g_file, conn->peerAddr().toIpPort().c_str());

        conn->setHighWaterMarkCallback(onHighWaterMark, kBufSize+1);

        FILE* fp = ::fopen(g_file, "rb");
        if (fp)
        {
            // 使用shard_ptr管理fp存在周期，RAII机制管理资源
        FilePtr ctx(fp, ::fclose);
        conn->setContext(ctx);
        char buf[kBufSize];
        size_t nread = ::fread(buf, 1, sizeof buf, fp);
        conn->send(buf, static_cast<int>(nread));
        }
        else
        {
        conn->shutdown();
        LOG_INFO("FilerServer - no such file");
        }
    }
}

void onWriteComplete(const TcpConnectionPtr& conn)
{
    const FilePtr& fp = std::any_cast<const FilePtr&>(conn->getContext());
    char buf[kBufSize];
    size_t nread = ::fread(buf, 1, sizeof buf, fp.get());
    if (nread > 0)
    {
        conn->send(buf, static_cast<int>(nread));
    }
    else
    {
        conn->shutdown();
        LOG_INFO("FileServer - done");
    }
}

int main(int argc, char* argv[])
{
    LOG_INFO("pid = %d", getpid());
    if (argc > 1)
    {
        g_file = argv[1];

        EventLoop loop;
        InetAddress listenAddr(2022);
        TcpServer server(&loop, listenAddr, "FileServer");
        server.setConnectionCallback(onConnection);
        server.setWriteCompleteCallback(onWriteComplete);
        server.start();
        loop.loop();
    }
    else
    {
        fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
    }
}

