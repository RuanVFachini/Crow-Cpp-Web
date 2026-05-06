! #/bin/bash

g++ ./CrowApi/main.cpp -o app -lpthread -lssl -lcrypto
./app
