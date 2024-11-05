### Proxy server


### Build:

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

