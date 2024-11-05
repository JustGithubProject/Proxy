#include "intermediate_server.hpp"

#include <iostream>

const int KBYTE = 1024;

IntermediateServer::IntermediateServer()
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9030)),
    buffer(KBYTE)
{}
IntermediateServer::~IntermediateServer() {}


void IntermediateServer::parseRequestFromClient(std::string& host, std::string& port) {
    std::string request(buffer.begin(), buffer.end());
    std::regex hostRegex(R"(Host:\s*([^\s:]+)(?::(\d+))?)", std::regex::icase);
    std::smatch match;

    if (std::regex_search(request, match, hostRegex)) {
        host = match[1];
        port = match[2].str().empty() ? "80" : match[2].str();
    } else {
        throw std::runtime_error("Host header not found in request");
    }
}

void IntermediateServer::run() {
    getRequestFromClient();
}


void IntermediateServer::getRequestFromClient() {
    for (;;) {
        boost::asio::ip::tcp::socket clientSocket(io_context);
        acceptor.accept(clientSocket);
        std::cout << "IntermediateServer got connection(client)!" << std::endl;

        boost::system::error_code error;
        size_t numberOfReadBytes = clientSocket.read_some(boost::asio::buffer(buffer), error);
        if (error == boost::asio::error::eof) {
            std::cout << "The client has been disconnected" << std::endl;
        } else if (error) {
            throw boost::system::system_error(error);
        }

        std::cout << "Received data: ";
        std::cout.write(buffer.data(), numberOfReadBytes);
        std::cout << std::endl;

        redirectRequest(numberOfReadBytes);
        sendResponseBackToSourceClient(clientSocket);
    }
}

void IntermediateServer::sendResponseBackToSourceClient(boost::asio::ip::tcp::socket& clientSocket) {
    boost::system::error_code error;
    boost::asio::write(clientSocket, responseFromTargetServer);
    if (error) {
        std::cerr << "Failed to send data" << error.message() <<  std::endl;
    } else {
        std::cout << "The data has been sent successfully" << std::endl;
    }
}


void IntermediateServer::redirectRequest(size_t numOfBytes) {
    // Getting target host and port
    std::string targetHost;
    std::string targetPort;
    parseRequestFromClient(targetHost, targetPort);

    boost::asio::ip::tcp::socket targetServerSocket(io_context);
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(targetHost, targetPort);

    // Connection to target server
    boost::asio::connect(targetServerSocket, endpoints);
    std::cout << "Connected to target server successfully" << std::endl;

    boost::system::error_code error;
    boost::asio::write(targetServerSocket, boost::asio::buffer(buffer, numOfBytes), error);

    if (error) {
        throw boost::system::system_error(error);
    }

    // Getting response from target server
    getResponseFromTargetServer(targetServerSocket);
}


void IntermediateServer::getResponseFromTargetServer(boost::asio::ip::tcp::socket& targetServerSocket) {
    boost::system::error_code error;
    boost::asio::read_until(targetServerSocket, responseFromTargetServer, "\r\n", error);

    if (error && error != boost::asio::error::eof) {
        throw boost::system::system_error(error);
    }
}