# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Korean game programming tutorial repository containing progressive C/C++ game examples from a book titled "한 시간 만에 게임 만들기" (Making Games in One Hour). The repository contains numbered directories (0-9) with increasingly complex game implementations.

## Project Structure

- **Numbered directories (0-9)**: Progressive game examples, each containing:
  - `source.cpp`: Main game implementation
  - `Project1.sln`: Visual Studio solution file
  - `Project1.vcxproj`: Visual Studio project file
  - `Project1.vcxproj.user`: Visual Studio user settings
- **README.md**: Book information and contact details in Korean
- **Appendix directories**: Additional examples and implementations

## Game Progression

- **0Hello world/**: Basic "Hello World" console output
- **1/**: RPG-style combat system with character stats, monsters, and battle mechanics
- **2/**: Enhanced combat with additional features
- **3/**: Further expanded RPG mechanics
- **4-4/, 4-4-2/**: Intermediate implementations
- **5-7/**: Advanced game features
- **8 Appendix1/, 9 Appendix2/**: Complex implementations including strategy game mechanics (daimyo lords, castles, troops)

## Development Environment

- **Platform**: Windows-based development using Visual Studio
- **Language**: C/C++ with some C++ STL usage (vectors, algorithms) in later examples
- **Dependencies**: Standard C libraries (stdio.h, stdlib.h, time.h, conio.h)

## Code Architecture

Each game example follows a similar structure:
1. Header includes at the top
2. Constant definitions (#define)
3. Enumeration constants for game states/types
4. Structure definitions for game entities
5. Global variable declarations
6. Function implementations
7. Main game loop

The games progressively introduce:
- Basic I/O and console manipulation
- Character/monster data structures
- Combat mechanics and game state management
- Complex data structures (vectors, algorithms)
- Multi-entity game systems (lords, castles, troops)

## Building and Running

Each directory contains a complete Visual Studio project that can be built independently:
- Open the `.sln` file in Visual Studio
- Build and run the project
- Most examples require console interaction

## Code Conventions

- Korean comments throughout the codebase with numbered organization system
- Function and variable names use camelCase or snake_case
- Extensive use of enums for game state management
- Structures used for entity data (characters, castles, lords)
- Global arrays for game data storage

## Notes

- All source code contains Korean language comments and string literals
- The codebase serves as educational material progressing from simple to complex game concepts
- Each example is self-contained and can be studied independently
- Later examples demonstrate more advanced C++ features and game programming concepts
- how to build and run of 1 directory
- write down the build and run guide to CLADUE.md in 1 directory