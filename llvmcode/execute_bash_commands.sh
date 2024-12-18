#!/bin/bash

# Check if a file is passed as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

# Get the file path from the argument
file="$1"

# Check if the file exists
if [ ! -f "$file" ]; then
    echo "File not found: $file"
    exit 1
fi

# Read the file and extract the lines between ;;startofbash and ;;endofbash
commands=$(sed -n '/;;startofbash/,/;;endofbash/p' "$file" | sed '1d;$d')

# Debugging step to show the extracted commands
echo "Extracted commands: $commands"

# Execute each command in the extracted section
while IFS= read -r line; do
    # Remove leading semicolons (if any)
    line="${line#\;}"

    # Ignore empty lines
    if [ -z "$line" ]; then
        continue
    fi

    # Execute the command
    echo "Executing: $line"
    eval "$line" || { echo "Command failed: $line"; exit 1; }
done <<< "$commands"
