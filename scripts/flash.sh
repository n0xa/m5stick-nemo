#!/usr/bin/env bash

set -eu

# Define the script usage
usage() {
    cat <<EOF
Usage: $0 [options]
Options:
    --build-config=./configs/.env.M5Cardputer   The .env file to use.
    --device=/dev/ttyUSB0           The device.
EOF
}

# Parse the arguments
for arg in "$@"; do
    case $arg in
        --build-config=*)       BUILD_CONFIG="${arg#*=}" ;;
        --device=*)           device="${arg#*=}" ;;
        *)                  usage ;;
    esac
done

BUILD_CONFIG=${BUILD_CONFIG:-./configs/.env.M5Cardputer}

if [ -z "$device" ]; then
    usage
    exit 1
fi

set -eu

echo "Running with config: $BUILD_CONFIG and device $device"
cat $BUILD_CONFIG
source $BUILD_CONFIG

docker run --rm -it -v $(pwd):/m5stick-nemo --device=$device m5stick-nemo/arduino-build-cli:test esptool.py --port $device erase_flash
if [[ "${LOCALE}" == "en-us" ]]; then
  output_file="M5Nemo-${NAME}.bin"
else
  output_file="M5Nemo-${NAME}.${LOCALE}.bin"
fi

docker run --rm -it -v $(pwd):/m5stick-nemo --device=$device m5stick-nemo/arduino-build-cli:test esptool.py --port $device write_flash -z 0 /m5stick-nemo/build/${output_file}
