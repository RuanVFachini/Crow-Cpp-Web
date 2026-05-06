! #/bin/bash

g++ ./CrowApi/main.cpp -o app  -g -lpthread -lssl -lcrypto
./app
