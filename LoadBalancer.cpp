/**
 * @file LoadBalancer.cpp
 * @brief Implements the LoadBalancer class that manages web servers and distributes network requests.
 */
 
#include "LoadBalancer.h"
#include <iostream>
#include <algorithm>

using namespace std;

LoadBalancer::LoadBalancer(size_t maxNumServers)
    : maxNumServers(maxNumServers), nextServerID(1){

    //Activate initial servers
    for (size_t i = 0; i < maxNumServers; i++){
        addServer(0);
    }
}

LoadBalancer::~LoadBalancer() {
    for (size_t i = 0; i < runningServers.size(); i++) {
        delete runningServers[i];
    }
    for (size_t i = 0; i < notRunningServers.size(); i++) {
        delete notRunningServers[i];
    }
}


void LoadBalancer::distributeReq(const Request& request, int currTime){ //gives a new request to a server to process only if it is available or adds it to the main queue
    bool check = false;
    for (size_t i = 0; i < runningServers.size(); i++){
        if (runningServers[i]->isAvailable()){
            runningServers[i]->getReq(request, currTime);
            check = true;
            break;
        }
    }

    if (!check){
        reqQueue.push(request);
    }
}



void LoadBalancer::procQueuedReqs(int currTime){ //Processes queued requests by giving them to a server
    while (!reqQueue.empty()){
        bool check = false;
        for (size_t i = 0; i < runningServers.size(); i++){
            if (runningServers[i]->isAvailable()){
                runningServers[i]->getReq(reqQueue.front(), currTime);
                reqQueue.pop();
                check = true;
                break;
            }
        }

        if (!check){
            break;
        }
    }
}

void LoadBalancer::simTime(int currTime){ //Simulates time step in the system, updates servers and processes queued requests
    for (size_t i = 0; i < runningServers.size(); i++){
        runningServers[i]->fakeTime(currTime);
    }


    size_t numServers = runningServers.size();

    //Deactivate a server if queue size < 3 * number of servers
    if (reqQueue.size() < 3 * numServers && numServers > 1){
        deactivateServer(currTime);
    }

    //Activate a server if queue size > 5 * number of servers & there are inactive servers
    if (reqQueue.size() > 5 * numServers && !notRunningServers.empty()){
        addServer(currTime);
    }

    procQueuedReqs(currTime);
}

void LoadBalancer::addServer(int currTime) {
    WebServer* newServer = nullptr;

    if (!notRunningServers.empty()) {
        newServer = notRunningServers.back(); //Reactivate inactive server
        notRunningServers.pop_back();
    } else if (nextServerID <= maxNumServers) {
        newServer = new WebServer(nextServerID++); //Create new server
    } else {
        //Max number of servers created
        return;
    }

    runningServers.push_back(newServer);
    cout << endl;
    cout << "<span style=\"color:green;\">Clock Cycle: " << currTime << "</span><br>" << endl;
    cout << "   <span style=\"color:green;\">Old Number of Active Servers: " << runningServers.size()-1 << "</span><br>" << endl;
    cout << "   <span style=\"color:green;\">Queue Size: " << reqQueue.size() << "</span><br>" << endl;
    cout << "   <span style=\"color:green;\">Activated Server " << newServer->getServerID() << "</span><br>" << endl;
    cout << "   <span style=\"color:green;\">New Number of Active Servers: " << runningServers.size() << "</span><br>" << endl;

}

void LoadBalancer::deactivateServer(int currTime){
    if (runningServers.size() > 1){
        for (auto it = runningServers.begin(); it != runningServers.end(); ++it){
            WebServer* server = *it;
            if (server->isAvailable()){
                runningServers.erase(it);
                notRunningServers.push_back(server);
                cout << endl;
                cout << "<span style=\"color:red;\">Clock Cycle: " << currTime << "</span><br>" << endl;
                cout << "   <span style=\"color:red;\">Old Number of Active Servers: " << runningServers.size()+1 << "</span><br>" << endl;
                cout << "   <span style=\"color:red;\">Queue Size: " << reqQueue.size() << "</span><br>" << endl;
                cout << "   <span style=\"color:red;\">Deactivated Server " << server->getServerID() << "</span><br>" << endl;
                cout << "   <span style=\"color:red;\">New Number of Active Servers: " << runningServers.size() << "</span><br>" << endl;
                return;
            }
        }
        //If no idle servers are available, do not deactivate any server
    }
}


vector<int> LoadBalancer::getRunningServers() const{
    vector<int> serverIDs;
    for (size_t i = 0; i < runningServers.size(); i++){
        serverIDs.push_back(runningServers[i]->getServerID()); 
    }
    return serverIDs;
}

int LoadBalancer::getRunningServerCount() const {
    return runningServers.size();
}

int LoadBalancer::getRequestQueueSize() const {
    return reqQueue.size();
}

vector<int> LoadBalancer::getNotRunningServers() const {
    vector<int> serverIDs;
    for (size_t i = 0; i < notRunningServers.size(); i++) {
        serverIDs.push_back(notRunningServers[i]->getServerID());
    }
    return serverIDs;
}


