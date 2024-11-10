# pico-cpp

Bare minimum C++ project using the Raspberry Pi Pico SDK.

## Install (Linux)

Before you start, make sure you have a basic development environment set up. For
example, on Ubuntu, Raspberry Pi OS or other Debian-based systems:
```sh
sudo apt update
sudo apt install cmake build-essential git wget python3
```

Download a recent compiler from [**tttapa/docker-arm-cross-toolchain**](https://github.com/tttapa/docker-arm-cross-toolchain):
```sh
gcc_version=14
url=https://github.com/tttapa/docker-arm-cross-toolchain/releases/latest/download
mkdir -p ~/opt
wget $url/x-tools-arm-pico-eabi-gcc$gcc_version.tar.xz -O- | tar xJ -C ~/opt
```
(If you're using an ARM64 system, use `x-tools-aarch64-rpi3-linux-gnu-arm-pico-eabi-gcc$gcc_version.tar.xz`
instead of `x-tools-arm-pico-eabi-gcc$gcc_version.tar.xz`.)

Then also install the Pico SDK if you haven't already:
```sh
sdk_version=2.0.0
url=https://github.com/raspberrypi/pico-sdk
mkdir -p ~/pico
git clone $url --branch $sdk_version --recurse-submodules --shallow-submodules ~/pico/pico-sdk
```

If you installed either the compiler or the SDK in a different location, you
should edit `.vscode/cmake-kits.json` accordingly.

## Build (VSCode)

Make sure you have the Microsoft [**CMake Tools**](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension installed.
Then open the directory of this project in VSCode, and execute the following commands (using <kbd>Ctrl+Shift+P</kbd>):

 1. **CMake: Select a Kit**. Then select `RPi Pico ─ tttapa/arm-pico-eabi` as the active kit.
 2. **CMake: Delete Cache and Reconfigure**. (In case the extension doesn't configure the project automatically.)
 3. **CMake: Build** (<kbd>F7</kbd>).

## Build (CLI)

```sh
cd pico-cpp
export PICO_SDK_PATH="$HOME/pico/pico-sdk"
cmake -S . -B build --toolchain ~/opt/x-tools/arm-pico-eabi/arm-pico-eabi.toolchain.cmake
cmake --build build -j$(nproc)
```

## Deploy

Plug in the Pi Pico while pressing the program button. Then copy the compiled UF2 file to the Pico's USB drive:
```sh
cp build/hello.uf2 /media/$USER/RPI-RP2
```

## Check output

To see the output from the example program, use a utility such as GNU Screen:
```sh
screen /dev/ttyACM0 115200
```
Make sure to select the correct port and baud rate.
