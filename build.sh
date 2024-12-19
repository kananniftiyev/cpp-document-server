
					#!/bin/bash
					# Change to the build directory
					cd build || { echo "Failed to change directory to build"; exit 1; }
					# Run CMake
					cmake .. || { echo "CMake configuration failed"; exit 1; }
					# Build the project
					make || { echo "Build failed"; exit 1; }
					# Check if the binary was created
					if [ -f "./main" ]; then
					    echo "Binary 'main' successfully created."
					else
					    echo "Binary 'main' not found. Build might have failed."
					    exit 1;
					fi
					# Notify that the build is complete
					echo -e "\e[31mBuilt the project\e[0m"
					# Display a stylish running message
					echo -e "${GREEN}==============================="
					echo -e "${YELLOW}      Running the code..."
					echo -e "${GREEN}===============================${RESET}"
					# Run the main executable with any arguments passed to the script
					./main "$@"
					# Create bin directory if it doesn't exist
					mkdir -p ../bin
					# Move the binary to the bin directory
					if mv ./main ../bin; then
					    echo "Binary moved to ../bin"
					else
					    echo "Failed to move the binary to ../bin"
					fi
					