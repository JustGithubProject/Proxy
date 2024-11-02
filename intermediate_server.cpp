#include "intermediate_server.hpp"

IntermediateServer::IntermediateServer()
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(tcp::v4(), 13)),
    buffer(KBYTE){}
IntermediateServer::~IntermediateServer() {}


void IntermediateServer::getRequest() {
    for (;;) {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::cout << "IntermediateServer got connection(client)!" << std::endl;

        boost::system::error_code error;
        size_t numberOfReadBytes = socket.read_some(boost::asio::buffer(buffer), error);
        if (error == boost::asio::error::eof) {
            std::cout << "The client has been disconnected" << std::endl;
        } else if (error) {
            throw boost::system::system_error(error);
        }

        std::cout << "Received data: ";
        std::cout.write(buffer.data(), numberOfReadBytes);
        std::cout << std::endl;
    }
}


void IntermediateServer::redirectRequest() {

}
