#include "WebServer.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;


WebServer::WebServer() : available(true), remainingTime(0) {}

WebServer::~WebServer() {}

void WebServer::getReq(const Request& request) {
    reqQueue.push(request);
    cout << "Received new request from: " << request.incomingIP << endl << endl;
    if (available) {
        procNextReq();
    }
}

void WebServer::fakeTime(int cycles) {
    if (!available && remainingTime > 0) {
        remainingTime = remainingTime - cycles;
        this_thread::sleep_for(chrono::seconds(1));
        if (remainingTime <= 0) {
            reqQueue.pop();
            available = true;
            cout << "Request processed. Server is available." << endl;
            if (!reqQueue.empty()) {
                procNextReq(); 
            }
        }
    }
}


void WebServer::procNextReq() {
    if (reqQueue.empty() || !available) {
        return;
    }

    const Request& request = reqQueue.front();
    remainingTime = request.time;
    available = false;

    cout << "Starting processing request from " << request.incomingIP << " -> " << request.outgoingIP << endl;
    cout << "Job type: "  << request.jobType << endl;
    cout << "Processing time: " << request.time << " cycles" << endl;
    cout << endl;
}



bool WebServer::isAvailable() const {
    return available && reqQueue.empty();
}


bool WebServer::reqQueueIsEmpty() const {
    return reqQueue.empty();
}