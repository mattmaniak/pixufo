# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [UNRELEASED]

The great refactor

### Added

- Exit/Quit [distinction](https://ux.stackexchange.com/questions/50893/do-we-exit-quit-or-close-an-application) for Windows/Unix-like systems.
- Game Over inscription.

### Changed

- C++ Standard from C++11 to C++20.
- Codebase to match Google C++ Guide 100%-strictly.
- Lowered every font size.
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
