#include "client.hpp"

int main() {
    std::string url = "https://www.youtube.com/watch?v=g1BdojiKK4I&t=336s";
    Client client(url);
    client.startProcess();
}