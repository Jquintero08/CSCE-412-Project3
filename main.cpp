#include <fstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

int main(){
    int numServers;
    int simTime;

    srand(static_cast<unsigned>(time(0)));


    cout << "Enter the max # of servers: ";
    cin >> numServers;
    cout << "Enter the simulation time (in clock cycles): ";
    cin >> simTime;

    /*
    vector<WebServer*> servers;
    for (int i = 0; i < numServers; i++){  
        servers.push_back(new WebServer(i + 1));
    }
    */


    //Anything related to HTML output generated by ChatGPT
    ofstream out("output.html");
    if (!out.is_open()){
        cerr << "Failed to open output file." << endl;
        return 1;
    }
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    cout << "<!DOCTYPE html>" << endl;
    cout << "<html>" << endl; 
    cout << "<head><title>Simulation Output</title></head>" << endl;
    cout << "<body><pre>" << endl; // Use <pre> to preserve formatting

    LoadBalancer lb(numServers);

    for (int i = 0; i < numServers * 100; i++){
        int incomingIPPart = i % 255;
        int outgoingIPPart = i % 255;
        int processingTime = (rand() % 141) + 10;
        Request req("136.218.101." + to_string(incomingIPPart), "136.218.102." + to_string(outgoingIPPart), processingTime, 'P');
        lb.distributeReq(req, 0);
    }

    //double newReqProbability = 0.01;
    double newReqProbability = 0.0054; //Lowered so the load balancer can be shown (if too high, the queue stays full and no servers can deactivate)

    for (int currTime = 1; currTime <= simTime; currTime++){
        lb.simTime(currTime);

        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue < newReqProbability){
            int incomingIPPart = rand() % 255;
            int outgoingIPPart = rand() % 255;
            //int processingTime = (rand() % 141) + 10;
            int processingTime = (rand() % 441) + 200;
            Request req("119.201.99." + to_string(incomingIPPart), "119.201.100." + to_string(outgoingIPPart), processingTime, 'P');
            lb.distributeReq(req, currTime);
        }

    }

    cout << "Simulation complete!" << endl;
    cout << "# of active servers @ end of simulation: " << lb.getRunningServerCount() << "<br>" << endl;

    vector<int> runningServerIDs = lb.getRunningServers();
    cout << "Active servers: ";
    for (size_t i = 0; i < runningServerIDs.size(); i++){
        cout << runningServerIDs[i];
        if (i < runningServerIDs.size() - 1){
            cout << ", ";
        }
    }
    cout << "<br>" << endl;


    vector<int> notRunningServerIDs = lb.getNotRunningServers();
    cout << "Deactivated servers: ";
    for (size_t i = 0; i < notRunningServerIDs.size(); i++) {
        cout << notRunningServerIDs[i];
        if (i < notRunningServerIDs.size() - 1){
            cout << ", ";
        }
    }
    cout << "<br>" << endl;

    cout << "Number of requests remaining in the queue: " << lb.getRequestQueueSize() << "<br>" << endl;

    //Anything related to HTML output generated by ChatGPT
    cout << "</pre></body>" << endl;
    cout << "</html>" << endl;


    cout.rdbuf(coutbuf);



    out.close();

    /*
    for (int i = 0; i < servers.size(); i++){
        delete servers[i];
    }
    */

    return 0;
}
