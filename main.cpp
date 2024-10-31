#include <iostream>
#include <string>

int main() {
    std::string url = "https://www.youtube.com/watch?v=ra058AnshbU";
    size_t posEndOfProtocol = url.find("://");
    size_t posStartOfHost = posEndOfProtocol + 3;
    std::string hostWithPath = url.substr(posStartOfHost);
    size_t posEndOfHost = hostWithPath.find("/");
    std::cout << hostWithPath.substr(posEndOfHost) << std::endl;


}