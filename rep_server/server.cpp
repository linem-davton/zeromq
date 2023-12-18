//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//
#include <zmq.hpp>
#include <string>
#include <sstream>
#include <format>

#include <cctype>

#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif
//#include "zhelpers.hpp"

int client_id(std::string request);

int main () {
    //  Prepare our context and socket
    zmq::context_t context (2);
    zmq::socket_t socket (context, zmq::socket_type::rep);
    socket.bind ("tcp://*:5555");

    // zmq::version 
    //s_version ();
    std::cout << "Hello World server in C++" << std::endl;


    while (true) {
        // request from client
        zmq::message_t request;

        //  Wait for next request from client - Blocking
        socket.recv (request, zmq::recv_flags::none);
        
        //  Do some 'work'
        sleep(1);
        int client_number = client_id(request.to_string());
         std::cout << "Received request" << request.to_string() << " from client " << client_id <<std::endl;
  
        //  reply to client, formatted string only supported in C++20 and above
        std::string reply_str = std::format("Hello Client {} How Can I help ",  client_number);
        
        zmq::message_t reply (reply_str.begin(), reply_str.end());

        //  Send reply back to client
        socket.send (reply, zmq::send_flags::none);
        
    }
    return 0;
}

int client_id(std::string request) {
    std::stringstream ss;

    for (char c : request) {
        if (std::isdigit(c)) {
            ss << c;
        }
    }
    int client_number;
    ss >> client_number;
    return client_number;
}