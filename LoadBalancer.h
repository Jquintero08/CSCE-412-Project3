#ifndef LOADBALANCER_H
#define LOADBALANCER_H

/**
 * @file LoadBalancer.h
 * @brief Declares the LoadBalancer class that manages web servers and distributes requests.
 */

#include "WebServer.h"
#include <vector>
#include <queue>

using namespace std;

/**
 * @class LoadBalancer
 * @brief Manages web servers and distributes network requests among them.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a LoadBalancer with a maximum number of servers.
     * @param maxNumServers Maximum number of servers allowed to be activated.
     */
    LoadBalancer(size_t maxNumServers);
    ~LoadBalancer();

    /**
     * @brief Gives a request to a server to process only if it is available or adds it to the main queue.
     * @param request The request to distribute.
     * @param currTime The current simulation time.
     */
    void distributeReq(const Request& request, int currTime); //gives a request to a server to process only if it is available or adds it to the main queue

    /**
     * @brief Simulates time step in the system, updates servers and processes queued requests.
     * @param currTime The current simulation time.
     */
    void simTime(int currTime); //Simulates time step in the system, updates servers and processes queued requests

    /**
     * @brief Returns the number of currently running (active) servers.
     * @return Number of active servers.
     */
    int getRunningServerCount() const;

    /**
     * @brief Returns a vector of IDs of currently running servers.
     * @return Vector of active server IDs.
     */
    vector<int> getRunningServers() const;

    /**
     * @brief Gets the number of remaining requests in the main queue.
     * @return Number of requests in the queue.
     */
    int getRequestQueueSize() const; //gets the number of remaining requests in the main queue

    /**
     * @brief Returns a vector of IDs of servers that are not running (inactive).
     * @return Vector of inactive server IDs.
     */
    vector<int> getNotRunningServers() const;

private:
    vector<WebServer*> runningServers; //Vector of active servers
    vector<WebServer*> notRunningServers; //Vector of idle servers
    queue<Request> reqQueue;

    size_t maxNumServers; //Maximum amount of servers allowed to be activated
    size_t minNumServers; //Minimum number of servers allowed to be activated (will automatically start up upon running the code)
    size_t nextServerID; 
    
    size_t idleServerCountToRemove; //How many idle servers before removing any
    size_t reqQueueSizeToAdd; //How many requests in queue to trigger the activation of a new server

    /**
     * @brief Processes queued requests by giving them to a server.
     * @param currTime The current simulation time.
     */
    void procQueuedReqs(int currTime); //Processes queued requests by giving them to a server

    /**
     * @brief Adds a new server to handle requests.
     * @param currTime The current simulation time.
     */
    void addServer(int currTime);

    /**
     * @brief Deactivates an idle server to save resources.
     * @param currTime The current simulation time.
     */
    void delServer(int currTime);

    /**
     * @brief Checks if the servers are being underutilized.
     * @return True if servers are underutilized.
     */
    bool checkServerUtil(); //Check if the servers are being underutilized
};

#endif
