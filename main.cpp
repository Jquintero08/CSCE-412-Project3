#include <fstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

int main(){
    int numberOfServers;
    int simTime;

    srand(static_cast<unsigned>(time(0)));


    cout << "Enter the number of servers: ";
    cin >> numberOfServers;
    cout << "Enter the simulation time (in clock cycles): ";
    cin >> simTime;

    vector<WebServer*> servers;
    for (int i = 0; i < numberOfServers; i++){  
        servers.push_back(new WebServer(i + 1));
    }
    LoadBalancer lb(servers);

    ofstream out("output.txt");
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    for (int i = 0; i < numberOfServers * 100; i++){
        int incomingIPPart = i % 255;
        int outgoingIPPart = i % 255;
        int processingTime = (rand() % 171) + 10;
        Request req("136.218.101." + to_string(incomingIPPart), "136.218.102." + to_string(outgoingIPPart), processingTime, 'P');
        lb.distributeReq(req, 0);
    }



    for (int currTime = 0; currTime < simTime; currTime++){
        lb.simTime(currTime);

        if (currTime % 50 == 0){
            int incomingIPPart = rand() % 255;
            int outgoingIPPart = rand() % 255;
            int processingTime = (rand() % 141) + 10;
            Request req("119.201.99." + to_string(incomingIPPart), "119.201.100." + to_string(outgoingIPPart), processingTime, 'P');
            lb.distributeReq(req, currTime);
        }
    }

    cout.rdbuf(coutbuf);
    out.close();

    for (int i = 0; i < servers.size(); i++){
        delete servers[i];
    }

    return 0;
}
