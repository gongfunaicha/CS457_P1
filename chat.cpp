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

string tolower(string src)
{
    // Helper function that converts a string to lowercase
    string res = "";
    unsigned int len_src = src.length();
    for (unsigned int i = 0; i < len_src;i++)
    {
        if ((src[i] >= 'A') && (src[i] <= 'Z'))
            res += (src[i] + 'a' - 'A');
        else
            res += src[i];
    }
    return res;
}

string checkip(string ip)
{
    unsigned int len_ip = ip.length();
    unsigned int subaddr = 0; // Used to store the subpart of addr, should be within 0 ~ 255
    unsigned int dotcount = 0; // Used to count the number of dots in ip
    if (tolower(ip) == "localhost")
    {
        // Special case for localhost
        return "localhost";
    }
    for (unsigned int i = 0; i < len_ip; i++)
    {
        // Every character must be '0~9' or '.'
        if ((ip[i] >= '0') && (ip[i] <= '9'))
        {
            if ((subaddr == 0) && (ip[i] == '0') && ((i+1) < len_ip) && (ip[i+1] != '.'))
            {
                // First character of the sub addr shouldn't be 0 except for only '0'
                return "InvalidIP";
            }
            subaddr *= 10;
            subaddr += (ip[i] - '0');
        }
        else if (ip[i] == '.')
        {
            dotcount++;
            if ((i == 0) || (ip[i-1] == '.')|| ((i+1) == len_ip))
            {
                // If dot is at first, last, or two consecutive dots, return Invalid IP
                return "InvalidIP";
            }
            if (subaddr > 255)
            {
                // Subaddr should be within 0 and 255
                return "InvalidIP";
            }
            subaddr = 0; // Next subaddr should start, clear the subaddr
        }
        else
        {
            // Neither 0 ~ 9  nor '.', return Invalid IP
            return "InvalidIP";
        }
    }
    // If survives, check the number of dots and last subaddr value
    if (dotcount != 3)
    {
        // Must be 3 dots in the ip string
        return "InvalidIP";
    }
    if (subaddr > 255)
    {
        // Subaddr should be within 0 and 255
        return "InvalidIP";
    }
    // All good, return ip
    return ip;
}

int main(int argc, char* argv[])
{
    // flag is used for differentiate different outcome
    // 0 = print help message, 1 = start server, 2 = start client
    int flag = 1;
    // two variables below are used in client mode
    string ip = "NoInput"; // "NoInput" for no input
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
        int i = 1;
        while (i <= 4)
        {
            if (strcmp(argv[i],"-p") == 0)
            {
                // If is -p, next argument should be port number
                string portnum = argv[++i]; // Assign CString port number to string
                port = parseportnum(portnum);
                if (port  == -2)
                {
                    // Determined invalid port number by parseportnum
                    cout << "Invalid Port Number" << endl;
                    flag = 0;
                    break;
                }
                i++;
            }
            else if (strcmp(argv[i],"-s") == 0)
            {
                // If is -s, next argument should be ip address
                string ipaux = argv[++i]; // Assign CString ip addr to string
                ip = checkip(ipaux);
                if (ip == "InvalidIP")
                {
                    // Determined invalid ip by checkip
                    cout << "Inavlid IP" << endl;
                    flag = 0;
                    break;
                }
                i++;
            }
            else
            {
                // Got invalid flag
                cout << "Invalid Flag Received" << endl;
                flag = 0;
                break;
            }
        }
        // Out of loop, check whether both port and ip received
        if ((port == -1) || (ip == "NoInput"))
        {
            // Either port not received or ip not received
            cout << "Both port and ip must be correctly provided." << endl;
            flag = 0;
        }
        else if (flag != 0)
        {
            // All good.
            flag = 2;
        }
    }
    else
    {
        // Invalid number of parameters, print error message then help message
        cout << "Invalid parameters" << endl;
        flag = 0;
    }

    // Start to handle different flag cases
    if (flag == 0)
    {
        // Flag == 0, display help message
        cout << "Usage: ./chat [OPTION...]" << endl;
        cout << "  -s=SERVER_IP\tSpecify the IP of the server to connect" << endl;
        cout << "  -p=Port_Num\tSpecify the port number of the server" << endl;
        cout << "  -h\t\tDisplay this help message" << endl;
        cout << endl;
        cout << "To start a server, simply type ./chat" << endl;
        cout << endl;
        cout << "To start a client, you must use both -s and -p flags" << endl;
        cout << "  For example, ./chat -s 127.0.0.1 -p 60000" << endl;
    }
    else if (flag == 1)
    {
        // Flag == 1, start server
    }
    else
    {
        // Flag == 2, start client
    }

    return 0;
}