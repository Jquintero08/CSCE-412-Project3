#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <queue>
#include <iostream>

using namespace std;

class WebServer {
public:
    WebServer();
    ~WebServer();
    void getReq(const Request& request);
    void procNextReq();
    bool isAvailable() const;
    void fakeTime(int cycles);
    bool reqQueueIsEmpty() const;

private:
    queue<Request> reqQueue;
    bool available;
    int remainingTime;
};

#endif
