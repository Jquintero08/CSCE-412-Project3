#include "WebServer.h"
#include <iostream>

using namespace std;

WebServer::WebServer(int id){
    serverID = id;
    available = true;
    completionTime = 0;
}

WebServer::~WebServer(){}


void WebServer::getReq(const Request& request, int currTime){
    reqQueue.push(request);
    cout << endl;
    cout << "Clock Cycle: " << currTime << endl;
    cout << "   Server: " << serverID << " (Queuing request)" << endl;
    cout << "   From: " << request.incomingIP << endl;
    cout << "   To: " << request.outgoingIP << endl;
    cout << "   Time: " << request.time << " cycles" << endl;

    if (available){
        procNextReq(currTime);
    }
}

void WebServer::procNextReq(int currTime){
    if (reqQueue.empty() || !available){
        return;
    }

    Request request = reqQueue.front();
    completionTime = currTime + request.time;
    available = false;
    cout << endl;
    cout << "Clock Cycle: " << currTime << endl;
    cout << "   Server " << serverID << " (Processing request) " << endl;
    cout << "   From: "<< request.incomingIP << endl;
}


void WebServer::fakeTime(int currTime){
    if (!available){
        if (currTime >= completionTime){
            cout << endl;
            cout << "Clock Cycle: " << currTime << endl;
            cout << "   Server " << serverID << " (Completed request)" << endl;
            cout << "   From: " << reqQueue.front().incomingIP << endl;
            reqQueue.pop();
            available = true;
            
            if (!reqQueue.empty()){
                procNextReq(currTime);
            }
        }
    }
}

bool WebServer::isAvailable() const{
    return available && reqQueue.empty();
}

bool WebServer::reqQueueIsEmpty() const {
    return reqQueue.empty();
}
