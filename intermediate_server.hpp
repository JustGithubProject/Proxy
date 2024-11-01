#pragma once

class IntermediateServer {
public:
    IntermediateServer();
    ~IntermediateServer();

    void getRequest();
    void redirectRequest();
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(tcp::v4(), 13));
};