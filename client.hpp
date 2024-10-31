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
    void sendRequestAndGetResponse();
private:
    boost::asio::io_service io_service;
    boost::asio::ssl::context ssl_context;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
    std::string urlToTargetServer_;

    uint32_t parseURLProtocol();
    std::string parseURLHost();
    std::string parseURLPath();
};