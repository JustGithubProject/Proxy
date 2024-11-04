#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdint>


class Client {
public:
    Client(std::string& urlToTargetServer);
    ~Client();

    void startProcess();

    void sendRequest();
    void getResponse();
private:
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    std::string urlToTargetServer_;

    uint32_t parseURLProtocol();
    std::string parseURLHost();
    std::string parseURLPath();
};