#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <queue>
#include <iostream>


using namespace std;

class WebServer {
public:
    WebServer(int id);
    ~WebServer();

    void getReq(const Request& request, int currTime);
    void procNextReq(int currTime);
    bool isAvailable() const;
    void fakeTime(int currTime);

    bool reqQueueIsEmpty() const;

private:
    queue<Request> reqQueue;
    bool available;
    int completionTime;
    int serverID;
};

#endif
