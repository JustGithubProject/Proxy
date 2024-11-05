# Proxy Server

This project implements a proxy server using C++ and the Boost libraries. The proxy server can intercept and manage client requests to an intermediate server, enabling functionalities like load balancing, caching, and secure communication.

Before building the project, ensure you have the following installed:

- C++ compiler (g++)
- Boost libraries (system, thread)
- OpenSSL libraries (ssl, crypto)

You can install the required libraries on Ubuntu using:

```
sudo apt-get install libboost-all-dev libssl-dev
```


### Build

```
    g++ -o proxy_start proxy_start.cpp intermediate_server.cpp -lboost_system -lboost_thread -lssl -lcrypto
```

```
    g++ -o client_start client_start.cpp client.cpp -lboost_system -lboost_thread -lssl -lcrypto
```

```
    ./proxy_start
```

```
    ./client_start
```

