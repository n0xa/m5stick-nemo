FROM python:3.6-slim

ENV PYTHONBUFFERED=1

# Install required packages and tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl \
    bash \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/bin sh

# Ensure pip is installed and upgrade it
RUN python3 -m ensurepip
RUN pip3 install --no-cache --upgrade pip setuptools pyserial esptool

# Install 32-bit C++ standard library
RUN apt-get update && apt-get install -y --no-install-recommends \
    lib32stdc++6 \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Install m5stack boards
COPY ./package_m5stack_index.json /package_m5stack_index.json
RUN arduino-cli core install m5stack:esp32 --additional-urls "file:///package_m5stack_index.json" --log-level warn --verbose

RUN arduino-cli core search m5stack
RUN arduino-cli board listall
#
# Create a directory for the prerequisites script
RUN mkdir -p /deauth_prerequisites
COPY ./deauth_prerequisites/install_prerequisites_Linux.sh /deauth_prerequisites/install_prerequisites_linux.sh

# Make the script executable
RUN chmod +x /deauth_prerequisites/install_prerequisites_linux.sh

# Run the script
RUN /deauth_prerequisites/install_prerequisites_linux.sh

ARG LIBRARIES 

# Install required libraries
RUN arduino-cli lib install $LIBRARIES --log-level warn --verbose

COPY ./scripts/compile.sh /compile.sh
RUN chmod +x /compile.sh

COPY ./scripts/entrypoint.sh ./entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
