#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

using namespace std;

struct Request{
    string incomingIP;
    string outgoingIP;
    int time;
    char jobType;

    Request() : incomingIP(""), outgoingIP(""), time(0), jobType('P') {}

    Request(const string& in, const string& out, int t, char type): incomingIP(in), outgoingIP(out), time(t), jobType(type) {}

};

#endif
