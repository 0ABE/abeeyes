# AbeEyes

AbeEyes is a fun desktop application that draws animated Googly Eyes in a window on your desktop. The eyes follow your mouse cursor, blink, and add a playful touch to your workspace.

## Features
- Animated Googly Eyes that track your mouse
- Blinking and idle states for more lifelike behavior
- Lightweight and easy to run
- Cross-platform support (Windows, Linux, macOS)

## Getting Started

### Prerequisites
- C++20 compatible compiler
- [SDL2](https://www.libsdl.org/) and [SDL2_image](https://www.libsdl.org/projects/SDL_image/) libraries
- CMake (for building)

### Build Instructions
1. Clone the repository:
   ```sh
   git clone https://github.com/0ABE/abeeyes.git
   cd abeeyes
   ```
2. Create a build directory and run CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run the application:
   - On Windows: `AbeEyes.exe`
   - On Linux/macOS: `./AbeEyes`

## Project Structure
- `src/` - Main source code
- `build/` - Build output
- `libs/` - Third-party libraries
- `rsrc/` - Resource files (images, etc.)

## License
This project is licensed under the Universal Permissive License (UPL). See the [LICENSE](LICENSE) file for details.

## Credits
- Uses SDL2 and SDL2_image for graphics and window management
- Inspired by classic desktop toys and widgets
