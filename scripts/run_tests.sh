#!/bin/bash

OS=$(uname -s)

if [ "$OS" = "Linux" ]; then
  find $(pwd)/build -name "test_*" -type f -executable -print0 | xargs -0 -I % sh -c %
fi

if [ "$OS" = "Darwin" ]; then
  find $(pwd)/build -name "test_*" -type f -perm +111 -print0 | xargs -0 -I % sh -c %
fi
