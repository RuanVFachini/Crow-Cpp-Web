! #/bin/bash

g++ $(find CrowApi -name "*.cpp") \
    -std=c++20 \
    -I./include \
    -L./lib \
    -lsoci_core \
    -lsoci_postgresql \
    -lpq \
    -Wl,-rpath,'$ORIGIN/lib' \
    -o app \
    -g \
    -lpthread \
    -lssl \
    -lcrypto
./app
