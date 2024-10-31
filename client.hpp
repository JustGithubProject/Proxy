#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <cstdint>

class Client {
public:
    Client(std::string urlToTargetServer);
    ~Client();

    void sendRequest();
    void getResponse();
private:
    boost::asio::io_service io_service;
    ip::tcp::socket socket(io_service);
    std::string urlToTargetServer_;

    uint32_t parseURLProtocol();
    std::string parseURLHost();
    std::string parseURLPath();
};