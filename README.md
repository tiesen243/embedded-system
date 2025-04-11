# Embedded System Projects

This repository contains a collection of embedded system projects developed to demonstrate various concepts and applications in embedded programming. Each project is self-contained and focuses on a specific application or concept.

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

The projects in this repository are designed to explore different aspects of embedded systems, including sensor integration, actuator control, and communication protocols.

## Project Structure

The repository is organized as follows:

- `src/`  
  Contains the source code for the embedded applications. Each subdirectory within `src/` corresponds to a specific project.

- `examples/`  
  Provides example code snippets and test cases for various modules and functionalities.

- `Makefile`  
  A makefile to automate the build process for the projects.

- `.gitignore`  
  Specifies files and directories to be ignored by Git.

## Getting Started

To get started with any of the projects:

1. Clone the repository:

   ```bash
   git clone https://github.com/tiesen243/embedded-system.git
   ```
   
2. Navigate to the project directory:
   
   ```bash
   cd embedded-system
   ```
   
4. Build the project using the provided `Makefile`:

   ```bash
   make {file-name}
   ```
   
## Prerequisites

Ensure you have the following tools installed on your development environment:
- A C compiler suitable for embedded development (e.g., GCC for ARM)
- Make utility
- [Optional] Hardware development boards (e.g., FriendlyARM)

  Prerequisites

Ensure you have the following tools installed on your development environment:

    A C compiler suitable for embedded development (e.g., GCC for ARM)

    Make utility

    [Optional] An IDE like Keil uVision or STM32CubeIDE

    [Optional] Hardware development boards (e.g., STM32, ESP32)

## Usage

Each project within the src/ directory includes its own set of instructions and documentation. Refer to the README.md files within those subdirectories for detailed information on setting up and running the specific projects.

## License

This repository is open-source and available under the MIT License.
