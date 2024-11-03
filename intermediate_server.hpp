#pragma once

#include <boost/asio.hpp>
#include <vector>
#include <regex>

const KBYTE = 1024;

class IntermediateServer {
public:
    IntermediateServer();
    ~IntermediateServer();

    void getRequestFromClient();
    void getResponseFromTargetServer();
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;

    // Buffer to store incoming data
    std::vector<char> buffer;

    void redirectRequest();
    void parseRequestFromClient(std::string& host, std::string& port);
};