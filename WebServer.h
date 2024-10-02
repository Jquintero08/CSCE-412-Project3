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

    void getReq(const Request& request, int currTime); //Gets request and adds it to the server's request queue (only passes it through though)
    void procNextReq(int currTime); //Processes the next in queue for the server (the one that was just queued)
    bool isAvailable() const; //If server is open and its queue is empty, it is available (these two are the same, but it was easier for me to know what the use case was by differentiating the two)
    bool isIdle() const; //If server is open to new requests and queue is empty, set as idle
    void fakeTime(int currTime); //Simulates time for the server and checks if the current request is completed.

    bool reqQueueIsEmpty() const;
    int getServerID() const; 

private:
    queue<Request> reqQueue; //Each server's queue. (only can pass in a request though)
    //I got the instructions wrong and thought each server had its own queue, so instead of refactoring my entire code, I made it to where the queue is just used to pass requests in rather than hold them
    bool available;
    int completionTime;
    int serverID;
};

#endif
