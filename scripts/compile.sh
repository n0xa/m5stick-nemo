#!/bin/bash

# Define the script usage
usage() {
    cat <<EOF
Usage: $0 [options]
Options:
    --locale=LOCALE                 The locale.
    --name=NAME                     The name.
    --fqbn=FQBN                     The fully-qualified board name.
    --extra-flags=EXTRA_FLAGS       Extra flags.
    --libraries=LIBRARIES           Libraries.
    --bootloader-addr=BOOTLOADER_ADDR
                                    Bootloader address.
EOF
}

# Parse the arguments
for arg in "$@"; do
    case $arg in
        --locale=*)         locale="${arg#*=}" ;;
        --name=*)           name="${arg#*=}" ;;
        --fqbn=*)           fqbn="${arg#*=}" ;;
        --extra-flags=*)    extra_flags="${arg#*=}" ;;
        --libraries=*)      libraries="${arg#*=}" ;;
        --bootloader-addr=*) bootloader_addr="${arg#*=}" ;;
        *)                  usage ;;
    esac
done


# Check if required arguments are provided
if [ -z "$locale" ] || [ -z "$name" ] || [ -z "$fqbn" ] || [ -z "$extra_flags" ] || [ -z "$libraries" ] || [ -z "$bootloader_addr" ]; then
    usage
    exit 1
fi

# Use the provided arguments
echo "Starting Compilation"
echo "Locale: $locale"
echo "Name: $name"
echo "FQBN: $fqbn"
echo "Extra flags: $extra_flags"
echo "Libraries: $libraries"
echo "Bootloader address: $bootloader_addr"

locale=${LOCALE:-en-us}
language=$(echo "LANGUAGE_${locale//-/_}" | tr '[:lower:]' '[:upper:]')

extra_flags="${EXTRA_FLAGS} -D${language}"

arduino-cli compile --log \
  --fqbn $fqbn \
  -e \
  --build-property build.partitions=huge_app \
  --build-property upload.maximum_size=3145728 \
  --build-property compiler.cpp.extra_flags="${extra_flags}" \
  --output-dir ./m5stick-nemo/build \
  ./m5stick-nemo/m5stick-nemo.ino

if [[ "${locale}" == "en-us" ]]; then
  output_file="M5Nemo-${name}.bin"
else
  output_file="M5Nemo-${name}.${locale}.bin"
fi

echo "Merging binaries to ${output_file}"

esptool.py --chip esp32s3 merge_bin --output ./m5stick-nemo/build/${output_file}  \
            ${bootloader_addr} ./m5stick-nemo/build/m5stick-nemo.ino.bootloader.bin \
            0x8000 ./m5stick-nemo/build/m5stick-nemo.ino.partitions.bin \
            0x10000 ./m5stick-nemo/build/m5stick-nemo.ino.bin
