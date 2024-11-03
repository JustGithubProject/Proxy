#include "intermediate_server.hpp"

IntermediateServer::IntermediateServer()
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(tcp::v4(), 13)),
    buffer(KBYTE)
{}
IntermediateServer::~IntermediateServer() {}


void IntermediateServer::parseRequestFromClient(std::string& host, std::string& port) {
    std::string request(buffer.begin(), buffer.end());
    std::regex hostRegex(R"(Host:\s*([^\s:]+)(?::(\d+))?)", std::regex::icase);
    std::smatch match;

    if (std::regex_search(request, match, hostRegex)) {
        host = match[1];
        port = match[2].str().empty() ? "80" : match[2];
    } else {
        throw std::runtime_error("Host header not found in request");
    }
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

}
