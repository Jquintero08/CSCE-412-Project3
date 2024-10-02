#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include <vector>
#include <queue>

using namespace std;

class LoadBalancer {
public:
    LoadBalancer(int maxNumServers);
    ~LoadBalancer();
    void distributeReq(const Request& request, int currTime); //gives a request to a server to process only if it is available or adds it to the main queue
    void simTime(int currTime); //Simulates time step in the system, updates servers and processes queued requests
    int getRunningServerCount() const;
    vector<int> getRunningServers() const;
    int getRequestQueueSize() const; //gets the number of remaining requests in the main queue
    vector<int> getNotRunningServers() const;

private:
    vector<WebServer*> runningServers; //Vector of active servers
    vector<WebServer*> notRunningServers; //Vector of idle servers
    queue<Request> reqQueue;

    int maxNumServers; //Maximum amount of servers allowed to be activated
    int minNumServers; //Minimum number of servers allowed to be activated (will automatically start up upon running the code)
    int nextServerID; 
    
    int idleServerCountToRemove; //How many idle servers before removing any
    int reqQueueSizeToAdd; //How many requests in queue to trigger the activation of a new server

    void procQueuedReqs(int currTime); //Processes queued requests by giving them to a server
    void addServer(int currTime);
    void delServer(int currTime);
    bool checkServerUtil(); //Check if the servers are being underutilized
};

#endif
