#!/bin/bash

# Check if any command-line arguments were passed
if [ $# -eq 0 ]; then
    # If no arguments, start an interactive bash shell
    /bin/bash
else
    # If arguments, run the provided command
    exec "$@"
fi

