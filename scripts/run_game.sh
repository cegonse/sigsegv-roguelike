#!/bin/bash

mkdir -p ./build/assets
cp -r ./test_assets/* ./build/assets

./build/game
