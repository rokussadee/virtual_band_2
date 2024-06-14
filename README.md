# Virtual Band 2

## Concept
Virtual Band 2 is an innovative application designed to integrate symbolic music generation using AI with Digital Audio Workstations (DAWs). The project aims to provide real-time music generation capabilities using OpenAI's GPT models, allowing musicians to create and manipulate musical compositions interactively.

## Goals
1. **Integrate AI for Music Generation**: Utilize OpenAI's GPT models to generate symbolic music information in real-time.
2. **Seamless DAW Integration**: Ensure smooth integration with popular DAWs to leverage their timing and recording features.
3. **User-Friendly Interface**: Develop an intuitive and visually appealing user interface for ease of use.
4. **Real-Time MIDI Processing**: Enable real-time processing and generation of MIDI events.

## Challenges
- **C++ and JUCE Development**: As a beginner in C++ and JUCE, the learning curve was steep. The audio VST development community is niche, offering limited resources for troubleshooting.
- **Symbolic Music Generation Models**: Existing models like the Anticipatory Music Transformer were too slow for real-time use. OpenAI's GPT provided a more accessible but less musically adept solution.
- **Cross-Application Workflows**: Integrating Python MIDI scripting, C++, API calls, and DAW usage significantly increased the project's complexity.

## Current State
- The application currently builds and runs as a standalone application.
- VST3 and .component builds are not functioning properly in the test environment.
- Rigorous testing across different builds and environments has not yet been conducted.
- The project is still in an early stage of development.

## Next Steps
1. **Implement OpenAI API Responses**: Integrate OpenAI API responses natively in C++ using the openai-cpp package.
2. **Improve MIDI Timing Information**: Enhance the logging process to include accurate MIDI timing information.
3. **UI Implementation**: Apply the design mockups and style guides to the PluginEditor in C++.
4. **Remote MIDI Scripts**: Enable Remote MIDI scripts to utilize Ableton Live set information in the generation process.
5. **VST3 and AU Builds**: Work on getting VST3 and AU builds functioning to fully utilize DAW features.
6. **Flexible Generation/Prompting**: Allow for variations in style, genre, speed, and other musical aspects in the generative process.

## Installation Guide

### Prerequisites
- **Operating System**: macOS
- **Package Manager**: Homebrew
- **C++ Compiler**: Xcode Command Line Tools
- **CMake**: Installed via Homebrew
- **Python**: Installed via Homebrew

### Installation Steps

1. **Install Homebrew**:
   ```sh
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
2. **Install CMake**:

  ```sh
  brew install cmake
  ```

3. **Install Xcode Command Line Tools**:

  ```sh
  xcode-select --install
  ```
4. **Install Python**:

  ```sh
  brew install python
  ```
5. **Clone the Repository**:

  ```sh
  git clone https://github.com/your-username/virtual_band_2.git
  cd virtual_band_2
  ```
6. **Set Up JUCE**:
Download JUCE from the JUCE website and place it in an accessible location.

7. **Install Dependencies**:
Ensure you have the dependencies listed in your CMakeLists.txt file installed. For the openai-cpp package, follow their installation guide.

8. **Build the Project**:

```sh
 cmake -S . -B build        
 cmake --build build --clean-first --verbose

```
9. **Run the Standalone Application**:
Use the IDE's built-in run-button or run it in the terminal.
```sh
./VirtualBand2_Standalone
```
## Notes

Documentation for Other Systems: Installation and usage instructions for other systems (Windows, Linux) will be added in the future. For now, refer to the respective documentation for tools like JUCE, CMake, and the openai-cpp package for guidance.

## References

Pamplejuce: [Pamplejuce GitHub Repository](https://github.com/sudara/pamplejuce)

openai-cpp: [openai-cpp GitHub Repository](https://github.com/olrea/openai-cpp)