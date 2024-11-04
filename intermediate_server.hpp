#pragma once

#include <boost/asio.hpp>
#include <vector>
#include <regex>

class IntermediateServer {
public:
    IntermediateServer();
    ~IntermediateServer();

    void run();

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;

    // Buffer to store incoming data
    std::vector<char> buffer;
    boost::asio::streambuf responseFromTargetServer;

    void getRequestFromClient();
    void getResponseFromTargetServer(boost::asio::ip::tcp::socket& targetServerSocket);
    void redirectRequest(size_t numOfBytes);
    void parseRequestFromClient(std::string& host, std::string& port);
    void sendResponseBackToSourceClient(boost::asio::ip::tcp::socket& clientSocket);
};