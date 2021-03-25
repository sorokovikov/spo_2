#!/bin/bash

clang++ server/main.cpp server/time.cpp -o server.out
echo "Server built."
clang++ client/main.cpp -o client.out
echo "Client built."