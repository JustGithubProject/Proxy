#include "client.hpp"

int main() {
    std::string url = "https://www.google.com/";
    Client client(url);
    client.startProcess();
}