#!/bin/bash

mkdir -p cmake-build && cd cmake-build && cmake .. -D CMAKE_BUILD_TYPE=Release && make
