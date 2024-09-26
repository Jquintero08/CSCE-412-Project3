#include "WebServer.h"
#include "Request.h"
#include <iostream>

int main() {
    WebServer server;
    
    server.getReq(Request("192.168.1.1", "192.168.1.5", 5, 'P'));
    server.getReq(Request("192.168.1.2", "192.168.1.6", 3, 'S'));

    while (!server.isAvailable() || !server.reqQueueIsEmpty()) { 
        server.fakeTime(1);
        std::cout << "Simulating processing time." << std::endl;
    }

    if (server.isAvailable()) {
        std::cout << "Server is available for more requests." << std::endl;
    } else {
        std::cout << "Server is still busy." << std::endl;
    }

    return 0;
}


//generated with chatgpt simply for testing. Will implement actual later