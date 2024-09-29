#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include <vector>
#include <queue>

using namespace std;

class LoadBalancer {
public:
    LoadBalancer(const vector<WebServer*>& servers);
    void distributeReq(const Request& request, int currTime);
    void simTime(int currTime);

private:
    vector<WebServer*> servers;
    queue<Request> reqQueue;
    
    void processQueuedRequests(int currTime);
};

#endif
