#include <iostream>
#include "environment.h"
#include "rtspconnectionclient.h"
#include "memory"
#include "thread"

typedef void (*RtspClientCallback)(const void *buff, int len, void *reserve);

class RtspClient
{
private:
    class MyCallback : public RTSPConnection::Callback
    {
    public:
        RtspClientCallback _cb = nullptr;
        void *reserve = nullptr;
        virtual bool onData(const char *id, unsigned char *buffer, ssize_t size, struct timeval presentationTime)
        {
            if (_cb)
            {
                _cb(buffer, size, reserve);
            }

            // std::cout << id << " " << size << " ts:" << presentationTime.tv_sec << "." << presentationTime.tv_usec << std::endl;
            return true;
        }
    };

    Environment env;
    MyCallback cb;
    std::shared_ptr<RTSPConnection> rtspClient;
    std::shared_ptr<std::thread> th_mainloop;
    static void th_(RtspClient *cli)
    {
        printf("+++\n");
        cli->env.mainloop();
        printf("---\n");
    }

public:
    RtspClient(/* args */) {}
    ~RtspClient() {}

    void Open(std::string _url, RtspClientCallback _cb, void *reserve)
    {
        Stop();
        env.start();
        cb._cb = _cb;
        cb.reserve = reserve;
        rtspClient.reset(new RTSPConnection(env, &cb, _url.c_str()));
        th_mainloop.reset(new std::thread(th_, this));
    }

    void Stop()
    {
        env.stop();
        if (th_mainloop.get())
        {
            th_mainloop->join();
        }
    }
};
