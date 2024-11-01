#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdint>

// constants
const char* HOST = "127.0.0.1";
const int PORT = 8000;

class Client {
public:
    Client(std::string& urlToTargetServer);
    ~Client();

    void startProcess();

    void sendRequest();
    void getResponse();
private:
    boost::asio::io_service io_service;
    booost::asio::ip::tcp::socket socket(io_service);
    std::string urlToTargetServer_;

    uint32_t parseURLProtocol();
    std::string parseURLHost();
    std::string parseURLPath();
};