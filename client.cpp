#include "client.hpp"

Client::Client(std::string urlToTargetServer) 
    : urlToTargetServer_(urlToTargetServer){
    socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(HOST), PORT));
}


Client::~Client() {}


uint32_t parseURLProtocol() {
    size_t pos = urlToTargetServer.find("://");
    if (pos == 5) {
        return 443;
    }
    return 80;
}


std::string Client::parseURLHost() {
    size_t posEndOfProtocol = urlToTargetServer.find("://");
    size_t posStartOfHost = posEndOfProtocol + 3;
    std::string hostWithPath = urlToTargetServer.substr(posStartOfHost);
    size_t posEndOfHost = hostWithPath.find("/");
    return hostWithPath.substr(0, posEndOfHost)
}


std::string Client::parseURLPath() {
    size_t posEndOfProtocol = urlToTargetServer.find("://");
    size_t posStartOfHost = posEndOfProtocol + 3;
    std::string hostWithPath = urlToTargetServer.substr(posStartOfHost);
    size_t posEndOfHost = hostWithPath.find("/");
    return hostWithPath.substr(posEndOfHost);
}


void Client::sendRequest() {
    uint32_t gotProtocol = parseURLProtocol();
    std::string gotHost = parseURLHost();
    std::string gotPath = parseURLPath();

    // Sending request to server
    std::string getReqString = "GET " + gotPath + " HTTP/1.1\r\nHost: " + gotHost + "\r\nConnection: keep-alive\r\n\r\n";
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(getReqString), error);
    if (!error) {
        std::cout << "The client has been sent the request" << std::endl;
    } else {
        std::cerr << "Failed to send request" << std::endl;
    }
}


void Client::getResponse() {
    // Getting response from server
    boost::asio::streambuf receiveBuffer;
    boost::asio::read(socket, receiveBuffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "Received failed: " << error.message() << std::endl;
    } else {
        const char* data = boost::asio::buffer_cast<const char*>(receiveBuffer.data());
        std::cout << data << std::endl;
    }
}


void Client::startProcess() {
    sendRequest();
    getResponse();
}