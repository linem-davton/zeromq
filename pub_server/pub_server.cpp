//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>

#if (defined (WIN32))
#include <zhelpers.hpp>
#endif


int main () {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");			// Not usable on Windows.

    //  Initialize random number generator
    //srand (time (NULL));
    while (1) {

        int zipcode, temperature, relhumidity;

        //  Get values that will fool the boss
        zipcode     = rand ()% 100000;
        temperature = rand() % 50 - 10;
        relhumidity = rand () % 50 + 30;


        //  Send message to all subscribers
        std::string send_str = std::format("{} {} {}", 10001, temperature, relhumidity);
        
        std::cout << "Sending message: " << send_str << std::endl;
        zmq::message_t message(send_str.begin(), send_str.end());
        publisher.send(message, zmq::send_flags::none);
        
        sleep(2); // Sleep time in seconds

    }
    return 0;
}