# Space Invaders Clone

A simple space invaders clone that I have been working on while learning SFML. At the moment there are only 7 enemies and a single player. Enemies advance down the screen and the player can shoot at enemies. If the player is hit by an enemy the game ends. If the player kills all enemies, the game ends and if an enemy reaches the bottom of the screen the game also ends.

## Controls

Arrow keys to move. Space to shoot. Requires **SFML 2.5.X** or higher.

## Requirements for Building

- C++17 (or newer) compiler.
- Download Pre-built [SFML 2.5.x](https://www.sfml-dev.org/download/sfml/2.6.1/) binaries.
- [CMake 3.20+](https://cmake.org/download/) or newer (GUI recommended)

### For Windows

- MS Visual Studio 2022 or newer (NOT vscode), with "**Desktop C++ Development**" bundle.
- Please download "Visual C++ 64bit" edition of SFML; ignore others.
- Move your unzipped `SFML-2.5.x` folder to its own home, example: `C:/SFML/SFML-2.5.1`.
- Edit **line 21** in [CMakeLists.txt](CMakeLists.txt#L21), to set value `SFML_HOME` to folder path you moved SFML into (from previous step).

### For macOS (x64 & arm64)

- XCode 14 or newer from AppStore (with MacOS SDK)
- Please install SFML 2.5.x as **Frameworks**, not as "dylibs", as shown in [official SFML guide](https://www.sfml-dev.org/tutorials/2.6/start-osx.php).
- IMPORTANT: ensure you install SFML libs for your specific CPU arch.
- Download Apple Developer tools. After Xcode is installed, run this in your Terminal:

```bash
  sudo xcode-select --install
```

- After installing the CMake GUI, add its accompanying CLI to PATH, simply run the following command:

```bash
   sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
```

### For Linux Desktop

- Latest display drivers
- Use your OS package manager (`apt` or `yum`) to install SFML 2.5 or newer.
- Alternatively, you may build SFML 2.5 from source, see [official SFML docs](https://www.sfml-dev.org/tutorials/2.6/start-linux.php).

```bash
  sudo apt install libsfml-dev
```

## Build Instructions

Please see [BUILDING.md](BUILDING.md) for detailed instructions for each platform.

## Author

&copy; 2013, mshirlaw
