#include "WebServer.h"
#include <iostream>

using namespace std;

WebServer::WebServer(int id) : available(true), completionTime(0), serverID(id) {}

WebServer::~WebServer(){}


void WebServer::getReq(const Request& request, int currTime){
    reqQueue.push(request);
    cout << endl;
    cout << "Clock Cycle: " << currTime << "<br>" << endl;
    cout << "   Server: " << serverID << " (Queuing request)<br>" << endl;
    cout << "   From: " << request.incomingIP << "<br>" << endl;
    cout << "   To: " << request.outgoingIP << "<br>" << endl;
    cout << "   Time: " << request.time << " cycles<br>" << endl;

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
    cout << "Clock Cycle: " << currTime << "<br>" << endl;
    cout << "   Server " << serverID << " (Processing request)<br>" << endl;
    cout << "   From: " << request.incomingIP << "<br>" << endl;
}


void WebServer::fakeTime(int currTime){
    if (!available){
        if (currTime >= completionTime){
            cout << endl;
            cout << "Clock Cycle: " << currTime << "<br>" << endl;
            cout << "   Server " << serverID << " (Completed request)<br>" << endl;
            cout << "   From: " << reqQueue.front().incomingIP << "<br>" << endl;
            reqQueue.pop();
            available = true;
            
            if (!reqQueue.empty()){
                procNextReq(currTime);
            }
        }
    }
}

bool WebServer::isIdle() const{
    return available && reqQueue.empty();
}

bool WebServer::isAvailable() const{
    return available && reqQueue.empty();
}

bool WebServer::reqQueueIsEmpty() const {
    return reqQueue.empty();
}

int WebServer::getServerID() const {
    return serverID;
}
