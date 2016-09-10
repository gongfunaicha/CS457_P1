//
// Created by bennywang on 9/8/16.
//
#include <iostream>
#include <cstring>

using namespace std;

int parseportnum(string portnum)
{
    if (portnum.length() > 5)
    {
        // Shouldn't be larger than 99999
        return -2;
    }
    if (portnum.length() == 0)
    {
        // Portnum shouldn't be empty
        return -2;
    }
    for (unsigned int i = 0; i < portnum.length(); i++)
    {
        if ((portnum[i] < '0') or (portnum[i] > '9'))
        {
            // element must be a number
            return -2;
        }
    }
    if ((portnum[0] == '0') && (portnum.length() != 1))
    {
        // Portnum shouldn't start with zero
        return -2;
    }
    // Start to parse the portnum
    int port = 0;
    for (unsigned int i = 0; i < portnum.length(); i++)
    {
        port *= 10;
        port += (portnum[i] - '0');
    }
    if ((port < 0) || (port > 65535))
    {
        // Portnum must be in the correct range (0~65535)
        return -2;
    }
    return port;
}


int main(int argc, char* argv[])
{
    // flag is used for differentiate different outcome
    // 0 = print help message, 1 = start server, 2 = start client
    int flag = 0;
    // two variables below are used in client mode
    string ip = "noinput"; // "noinput" for no input
    int port = -1; // -1 for no input
    if (argc == 1)
    {
        // no extra parameters, server mode
        flag = 1;
    }
    else if (argc == 2)
    {
        // one extra parameter
        // if "-h", print help message
        // if others, print invalid parameter then print help message
        if (strcmp(argv[1], "-h") != 0)
        {
            cout << "Invalid parameter" << endl;
        }
        flag = 0;
    }
    else if (argc == 5)
    {
        // four extra parameters, might be client mode
        // Ignored for now
    }
    else
    {
        // Invalid number of parameters, print error message then help message
        cout << "Invalid parameters" << endl;
        flag = 0;
    }
    return 0;
}