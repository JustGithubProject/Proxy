#pragma once

#include <boost/asio.hpp>
#include <vector>

const KBYTE = 1024;

class IntermediateServer {
public:
    IntermediateServer();
    ~IntermediateServer();

    void getRequest();
    void redirectRequest();
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;

    // Buffer to store incoming data
    std::vector<char> buffer;
};