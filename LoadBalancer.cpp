#include "LoadBalancer.h"
#include <iostream>
#include <algorithm>

using namespace std;

LoadBalancer::LoadBalancer(size_t maxNumServers)
    : maxNumServers(maxNumServers), minNumServers(2), nextServerID(1),
      idleServerCountToRemove(2), reqQueueSizeToAdd(5) {

    //Activate initial servers to minimum amount of servers
    for (size_t i = 0; i < minNumServers; i++){
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


void LoadBalancer::distributeReq(const Request& request, int currTime){
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



void LoadBalancer::procQueuedReqs(int currTime){
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

void LoadBalancer::simTime(int currTime){
    for (size_t i = 0; i < runningServers.size(); i++){
        runningServers[i]->fakeTime(currTime);
    }
    procQueuedReqs(currTime);

    if ((reqQueue.size() > reqQueueSizeToAdd) && (runningServers.size() < maxNumServers)){
        addServer(currTime);
    } else if (runningServers.size() > minNumServers && checkServerUtil()){
        delServer(currTime);
    }
}

void LoadBalancer::addServer(int currTime) {
    WebServer* newServer = nullptr;

    if (!notRunningServers.empty()) {
        newServer = notRunningServers.back(); //Reactivate inactive server first
        notRunningServers.pop_back();
    } else if (nextServerID <= maxNumServers) {
        newServer = new WebServer(nextServerID++); //Create new server if possible
    } else {
        cout << "<span style=\"color:blue;\">Cannot add new server: maximum number of servers reached." << "</span><br>" <<endl; //Max Servers reached (?)
        return;
    }
    runningServers.push_back(newServer);
    cout << endl;
    cout << "<span style=\"color:green;\">Clock Cycle: " << currTime << "</span><br>" << endl;
    cout << "   <span style=\"color:green;\">Activated Server " << newServer->getServerID() << "</span><br>" << endl;
}


bool LoadBalancer::checkServerUtil(){
    size_t idleServers = 0;
    for (size_t i = 0; i < runningServers.size(); i++){
        if (runningServers[i]->isIdle()){
            idleServers++;
        }
    }
    return idleServers >= idleServerCountToRemove;
}

void LoadBalancer::delServer(int currTime){
    if (!runningServers.empty()){
        for (auto it = runningServers.begin(); it != runningServers.end(); ++it){
            WebServer* server = *it;
            if (server->isIdle()){
                runningServers.erase(it);
                notRunningServers.push_back(server);
                cout << endl;
                cout << "<span style=\"color:red;\">Clock Cycle: " << currTime << "</span><br>" << endl;
                cout << "   <span style=\"color:red;\">Deactivated Server " << server->getServerID() << "</span><br>" << endl;
                break;
            }
        }
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

std::vector<int> LoadBalancer::getNotRunningServers() const {
    vector<int> serverIDs;
    for (size_t i = 0; i < notRunningServers.size(); i++) {
        serverIDs.push_back(notRunningServers[i]->getServerID());
    }
    return serverIDs;
}


