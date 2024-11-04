#include "client.hpp"
#include "intermediate_server.hpp"

int main() {
    std::string url = "https://www.google.com/";
    IntermediateServer proxyServer;
    proxyServer.run();

    Client client(url);
    client.startProcess();


    return 0;
}