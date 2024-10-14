#ifndef WEBSERVER_H
#define WEBSERVER_H

/**
 * @file WebServer.h
 * @brief Declares the WebServer class for processing network requests.
 */

#include "Request.h"
#include <queue>
#include <iostream>


using namespace std;

/**
 * @class WebServer
 * @brief Represents a web server that processes network requests.
 */
class WebServer {
public:
    /**
     * @brief Constructs a WebServer with a unique ID.
     * @param id Unique identifier for the server.
     */
    WebServer(int id);

    /**
     * @brief Destructor for the WebServer.
     */
    ~WebServer();

    /**
     * @brief Gets request and adds it to the server's request queue (only passes it through though).
     * @param request The request to process.
     * @param currTime The current simulation time.
     */
    void getReq(const Request& request, int currTime);

    /**
     * @brief Processes the next in queue for the server (the one that was just queued).
     * @param currTime The current simulation time.
     */
    void procNextReq(int currTime);

    /**
     * @brief Checks if the server is available to process a new request.
     * @return True if the server is available.
     */
    bool isAvailable() const;

    /**
     * @brief Simulates time for the server and checks if the current request is completed.
     * @param currTime The current simulation time.
     */
    void fakeTime(int currTime);

    /**
     * @brief Gets the server's unique ID.
     * @return The server's ID.
     */
    int getServerID() const; 

private:

    /**
     * @brief Queue of requests to be processed by the server.
     */
    queue<Request> reqQueue;

    /**
     * @brief Indicates whether the server is available to process a new request.
     */
    bool available;

    /**
     * @brief The time at which the current request will be completed.
     */
    int completionTime;

    /**
     * @brief Unique identifier for the server.
     */
    int serverID;
};

#endif
