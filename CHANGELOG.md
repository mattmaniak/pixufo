# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [UNRELEASED]

## Added

- Entities speed randomization, except for the Player.
- Local Application Bundle removal on macOS with `make clean`.
- On-screen FPS meter for debug type of builds.

## Changed

- Absolute Player movement to relative. Now the Player's Sprite is centered on a screen while everything else moves in relation to it.
- Capitalization and naming rules to fit [Google C++ Guide](https://google.github.io/styleguide/cppguide.html) requirements.
- Centered the Menu logo.
- Compiler version requirement to `gcc` version `8` or above.
- Naming of some variables and members to a more standard in code.

## Removed

- Hitboxes debugging (disabled only).
- Old readme info that wasn't applicable anymore.

## [0.3.0] - 2024-07-24

The great refactor

### Added

- Exit/Quit [distinction](https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application) for Windows/Unix-like systems.
- Game Over inscription.
- Movable background animation in menus.

### Changed

- C++ Standard from C++11 to C++20.
- Codebase to match [Google C++ Guide](https://google.github.io/styleguide/cppguide.html) more strictly.
- Naming in codebase as some code elements were missing self-explanory names.
- Some in-game button texts to better explain what those buttons do.

## [0.2.0] - 2024-07-08

Bare macOS port

### Added

- Possibility to build a bare binary and play it on macOS.

### Changed

- C++ Coding Rules closer to the Google C++ Style Guide.

### Removed

- Windows build support.

## [2019-03-24-release] - 2019-03-24

Public release.

### Added

- Initial playability.
- Building for GNU/Linux and Windows using Make.
