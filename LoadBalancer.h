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

    /**
     * @brief Destructor for the LoadBalancer.
     */
    ~LoadBalancer();

    /**
     * @brief Distributes a request to an available server or adds it to the main queue.
     * @param request The request to distribute.
     * @param currTime The current simulation time.
     */
    void distributeReq(const Request& request, int currTime);

    /**
     * @brief Simulates a time step in the system, updating servers and processing queued requests.
     * @param currTime The current simulation time.
     */
    void simTime(int currTime);

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
    /**
     * @brief Vector of active servers.
     */
    vector<WebServer*> runningServers;

    /**
     * @brief Vector of idle servers.
     */
    vector<WebServer*> notRunningServers; //Vector of idle servers

    /**
     * @brief Main queue of requests waiting to be processed.
     */
    queue<Request> reqQueue;


    /**
     * @brief Maximum number of servers allowed to be activated.
     */
    size_t maxNumServers; //Maximum amount of servers allowed to be activated

    /**
     * @brief Next server ID to assign when creating new servers.
     */
    size_t nextServerID; 

    /**
     * @brief Processes queued requests by giving them to available servers.
     * @param currTime The current simulation time.
     */
    void procQueuedReqs(int currTime);

    /**
     * @brief Adds a new server to handle requests.
     * @param currTime The current simulation time.
     */
    void addServer(int currTime);

    /**
     * @brief Deactivates an idle server to save resources.
     * @param currTime The current simulation time.
     */
    void deactivateServer(int currTime);

};

#endif
