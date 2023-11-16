#include <SFML/Graphics.hpp>
#include <iostream>
#include "TCPClient.h"


int main()
{
    try {

        TCPClient testClient("10.187.52.16", 50000);
        std::cout << testClient.receiveMessage();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what();
    }

    return 0;
}