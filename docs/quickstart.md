# Quick start

## Linux

#### Prerequisites

* gcc version >= 4.8.1

#### Hello rectangle!

* Download the [latest release](https://github.com/bernhardfritz/libxd/releases/latest) for Linux
* Extract it somewhere you like
* Create a new file called e.g. `sketch.cpp`

```C++
#include <xd/xd.hpp>

using namespace xd;

void setup() {
    size(640, 480);
}

void draw() {
    rect(50, 50, 100, 100);
}

void destroy() {

}
```

* Open the libxd root directory in `Terminal`
* Compile the example

```bash
g++ -std=c++11 sketch.cpp -o sketch -Iinclude -Llib -lxd -lglad -lglfw3 -lrt -lm -ldl -lX11 -lpthread
```

* Run it

```bash
./sketch
```

#### Troubleshooting

During the compilation process you might get error messages about missing packages.

Use the following commands to check which packages you are missing:

```bash
dpkg -l build-essential
dpkg -l libgl1-mesa-dev
dpkg -l xorg-dev
```

Depending on which packages you are missing use the following commands to install them:

```bash
sudo apt-get install build-essential
sudo apt-get install libgl1-mesa-dev
sudo apt-get install xorg-dev
```

---

## macOS

#### Prerequisites

* gcc version >= 4.8.1

#### Hello rectangle!

* Download the [latest release](https://github.com/bernhardfritz/libxd/releases/latest) for macOS (Darwin)
* Extract it somewhere you like
* Create a new file called e.g. `sketch.cpp`

```C++
#include <xd/xd.hpp>

using namespace xd;

void setup() {
    size(640, 480);
}

void draw() {
    rect(50, 50, 100, 100);
}

void destroy() {

}
```

* Open the libxd root directory in `Terminal`
* Compile the example

```bash
g++ -std=c++11 sketch.cpp -o sketch -Iinclude -Llib -lxd -lglad -lglfw3 -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo
```

* Run it

```bash
./sketch
```

#### Troubleshooting

`gcc` is included with the `Command Line Tools` and can be installed by entering the following command:

```bash
xcode-select --install
```

---

## Windows

#### Prerequisites

* mingw-w64 version >= 4.8.1

#### Hello rectangle!

* Download the [latest release](https://github.com/bernhardfritz/libxd/releases/latest) for Windows (win32)
* Extract it somewhere you like
* Create a new file called e.g. `sketch.cpp`

```C++
#include <xd/xd.hpp>

using namespace xd;

void setup() {
    size(640, 480);
}

void draw() {
    rect(50, 50, 100, 100);
}

void destroy() {

}
```

* Open the libxd root directory in `cmd`
* Compile the example

```cmd
g++ -std=c++11 sketch.cpp -o sketch -Iinclude -Llib -lxd -lglad -lglfw3 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
```

* Run it

```cmd
.\sketch.exe
```

#### Troubleshooting

`mingw-w64` can be downloaded from the [mingw-w64 website](https://mingw-w64.org/). In the downloads section there is a link called `MingW-W64-builds` leading to the latest release on sourceforge.

For MinGW to work correctly, `sh.exe` i.e. `C:/Program Files/OpenSSH/bin/sh.exe` must not be in your path.
