#pragma once

#include <iostream>
#include <boost/asio.hpp>

class Client {
public:
    Client();
    ~Client();

    void sendRequest();
    void getResponse();
private:
    boost::asio::io_service io_service;
    ip::tcp::socket clientSocket(io_service);
};