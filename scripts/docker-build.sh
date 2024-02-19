#!/usr/bin/env bash

BUILD_CONFIG="./configs/.env.${1:-M5Cardputer}"

set -eu

echo "Running with config: $BUILD_CONFIG"
cat $BUILD_CONFIG
source $BUILD_CONFIG
docker build ./ --build-arg LIBRARIES="$LIBRARIES" -t m5stick-nemo/arduino-build-cli:test

mkdir -p build

docker run --rm -it -v $(pwd):/m5stick-nemo m5stick-nemo/arduino-build-cli:test /compile.sh --name="$NAME" --fqbn="$FQBN" --extra-flags="$EXTRA_FLAGS" --libraries="$LIBRARIES" --bootloader-addr="$BOOTLOADER_ADDR" --locale="$LOCALE"
