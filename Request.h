#ifndef REQUEST_H
#define REQUEST_H

/**
 * @file Request.h
 * @brief Defines the Request struct for handling network requests.
 */

#include <string>
#include <iostream>

using namespace std;

/**
 * @struct Request
 * @brief Represents a network request with IP addresses, processing time, and job type.
 */
struct Request{
    /**
     * @brief The incoming IP address.
     */
    string incomingIP;

    /**
     * @brief The outgoing IP address.
     */
    string outgoingIP;

    /**
     * @brief Time required to process the job.
     */
    int time;

    /**
     * @brief Job type ('P' for processing, 'S' for streaming).
     */
    char jobType;

    /**
     * @brief Default constructor initializing members to default values.
     */
    Request() : incomingIP(""), outgoingIP(""), time(0), jobType('P'){}

    /**
     * @brief Parameterized constructor to initialize a request with specific values.
     * @param in Incoming IP address.
     * @param out Outgoing IP address.
     * @param t Processing time in clock cycles.
     * @param type Job type ('P' for processing, 'S' for streaming).
     */
    Request(const string& in, const string& out, int t, char type): incomingIP(in), outgoingIP(out), time(t), jobType(type){}

};

#endif
