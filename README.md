# PixUfo

Enjoy the cosmic weightlessness and avoid enemies in a 2D space.

![image](screenshot.png "Gameplay of PixUfo")

## What so special?

Author's weightlessness steering - realistic movement and space-like steering created from scratch.

## Purpose

Make the game by learning C++ and random framework. In this case - SDL2.

## Warning

**As it's the past educational project, may contain low quality code.**

## Requirements

- at least HD display resolution,
- GNU/Linux or macOS,
- [development-only] g++ (gcc with libstdc++) with version >= 4.8.1.

## Gameplay

**Goal:** avoid the Nebulas (grey-red vechicles) by steering the Ufo using arrows. Note that there is no gravity. Menu buttons confirmation is done by clicking enter key and pausing the game by escape key. Unfortunately changing the system resolution with the game opened may break it's rendering.

## Disclaimer

Works well on GNU/Linux. On macOS a bare binary is build instead of [Application Bundles](https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFBundles/BundleTypes/BundleTypes.html) vel `.app`. On Windows some fonts are blended and Nebulas (enemies) position randomization doesn't work.

## Building a project

### Linux-based OS (TL:DR for Ubuntu)

```shell
sudo apt update &&
sudo apt install git git-lfs gcc g++ make libsdl2-dev libsdl2-ttf-dev &&
git clone https://gitlab.com/mattmaniak/pixufo.git &&
cd pixufo &&
make &&
./PixUfo
```

### macOS with Homebrew

```shell
brew update &&
brew install git git-lfs gcc g++ make sdl2 sdl2_ttf &&
git clone https://gitlab.com/mattmaniak/pixufo.git &&
cd pixufo &&
make &&
./PixUfo
```

### Remove object files

#### GNU/Linux and macOS

```shell
make clean
```

## Development

### Coding Style

Coding style is [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

#### Validating Coding Style

Python 3 is required.

```shell
python3 -m venv .venv &&
source .venv/bin/activate &&
python3 -m pip install -r python_packages.txt
```

Running C++ Linter

```shell
cpplint src/*
```
