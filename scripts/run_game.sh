#!/bin/bash

mkdir -p ./build/resources
cp -r ./test_resources/* ./build/resources

./build/game
