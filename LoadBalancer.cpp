#include "LoadBalancer.h"
#include <iostream>

using namespace std;

LoadBalancer::LoadBalancer(const vector<WebServer*>& serverList){
    for (int i = 0; i < serverList.size(); i++){
        servers.push_back(serverList[i]);
    }
}

void LoadBalancer::distributeReq(const Request& request, int currTime){
    bool check = false;
    for (int i = 0; i < servers.size(); i++){
        if (servers[i]->isAvailable()){
            servers[i]->getReq(request, currTime);
            check = true;
            break;
        }
    }

    if (!check){
        reqQueue.push(request);
    }
}



void LoadBalancer::processQueuedRequests(int currTime){
    while (!reqQueue.empty()){
        bool check = false;
        for (int i = 0; i < servers.size(); i++){
            if (servers[i]->isAvailable()){
                servers[i]->getReq(reqQueue.front(), currTime);
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
    for (int i = 0; i < servers.size(); i++){
        servers[i]->fakeTime(currTime);
    }
    processQueuedRequests(currTime);
}


