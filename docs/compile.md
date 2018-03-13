# Compiling libxd from source

Compiling libxd from source allows you to [run the examples](run.md). After a successful compilation you also have the option to [install libxd to your system](install.md).

## Linux

#### Prerequisites

* gcc version >= 4.8.1
* git version >= 1.6.5
* cmake version >= 3.1

#### Compiling

Open a terminal, navigate to a directory of your choice and enter the following commands in order:

```bash
git clone --recursive https://github.com/bernhardfritz/libxd.git
cd libxd
mkdir build
cd build
cmake ..
make
```

#### Troubleshooting

During the installation process you might get error messages about missing packages.

Use the following commands to check which packages you are missing:

```bash
dpkg -l build-essential
dpkg -l git
dpkg -l cmake
dpkg -l libgl1-mesa-dev
dpkg -l xorg-dev
```

Depending on which packages you are missing use the following commands to install them:

```bash
sudo apt-get install build-essential
sudo apt-get install git
sudo apt-get install cmake
sudo apt-get install libgl1-mesa-dev
sudo apt-get install xorg-dev
```

---

## macOS

#### Prerequisites

* gcc version >= 4.8.1
* git version >= 1.6.5
* cmake version >= 3.1

#### Compiling

Open a terminal, navigate to a directory of your choice and enter the following commands in order:

```bash
git clone --recursive https://github.com/bernhardfritz/libxd.git
cd libxd
mkdir build
cd build
cmake ..
make
```

#### Troubleshooting

During the installation process you might get error messages about missing commands.

Use the following commands to check what you are missing:

```bash
gcc --version
make --version
git --version
cmake --version
```

Both `gcc` and `make` will come with the `Command Line Tools` and can be installed by entering the following command:

```bash
xcode-select --install
```

The recommended way to install `git` and `cmake` is by using a package manager called [homebrew](https://brew.sh). Make sure you have it installed before you continue.

Once you have `homebrew` installed you can use the following commands to install `git` and `cmake`:

```bash
brew install git
brew install cmake
```

---

## Windows

#### Prerequisites

* git version >= 1.6.5
* cmake version >= 3.1
* mingw-w64 version >= 4.8.1

#### Compiling

Open up `cmd` and enter the following commands in order:

```bash
git clone --recursive http://github.com/bernhardfritz/libxd.git
cd libxd
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

#### Troubleshooting

`git` can be downloaded from the [git website](https://git-scm.com/). Look for the latest windows build, download and install it.

`cmake` can be downloaded from the [cmake website](https://cmake.org/). In the downloads section look for the latest release and download the `Windows win64-x64 Installer`. In case you are using a 32-bit version of Windows use the `Windows win32-x86 Installer` instead.

`mingw-w64` can be downloaded from the [mingw-w64 website](https://mingw-w64.org/). In the downloads section there is a link called `MingW-W64-builds` leading to the latest release on sourceforge.

For MinGW to work correctly, `sh.exe` i.e. `C:/Program Files/OpenSSH/bin/sh.exe` must not be in your path.