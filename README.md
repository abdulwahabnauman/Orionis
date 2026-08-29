# Orionis

A 2D top-down space shooter built with **C++** and **SFML 3**. Type in your name, blast waves of enemies across five escalating levels, dodge incoming fire, and climb the local leaderboard.

## Features

- **Persistent player profiles** — enter a username on first launch; scores and in-progress games are saved to disk
- **Resume-a-run support** — if the game is closed mid-session, it's backed up and offered back to you next time you log in
- **5 waves of enemies** with distinct spawn patterns, increasing in difficulty
- **Local leaderboard** (top 10) ranked by score, saved between sessions
- **Pause menu** with resume/quit
- **Customizable background** via the in-game Settings screen
- **Game-over screen** with your final score

## Controls

| Action | Key / Button |
|---|---|
| Move ship | `A` / `D` |
| Shoot | Left mouse click |
| Pause / resume | `P` |
| Back out of Leaderboard | `Esc` |
| Menu buttons (Play / Leaderboard / Customize) | Left mouse click |

## Requirements

- A C++17 (or newer) compiler — `g++` or `clang++`
- **[SFML 3.0+](https://www.sfml-dev.org/download/)** (Graphics, Window, System modules)

> This project uses the SFML 3 API (e.g. `sf::VideoMode({w, h})`, the new `pollEvent()`/`is<>()` event model), so an older SFML 2.x install will **not** compile it.

## Building & Running

1. **Install SFML 3** for your platform:
   - **macOS (Homebrew):** `brew install sfml`
   - **Linux (Debian/Ubuntu):** build from source or grab a recent package with SFML 3 (Ubuntu's default `libsfml-dev` is often still 2.x — check the version)
   - **Windows:** download the SFML 3 SDK from the official site, or use vcpkg: `vcpkg install sfml`

2. **Compile** from the project root:
   ```bash
   g++ main.cpp -o orionis -lsfml-graphics -lsfml-window -lsfml-system
   ```
   (On Windows/MinGW, add `-lsfml-graphics -lsfml-window -lsfml-system` the same way, or use the provided VS Code build task.)

3. **Run it from the project root** (important — asset/font/save-file paths are relative):
   ```bash
   ./orionis
   ```

## Project Structure

```
Orionis/
├── main.cpp              # Entry point / game loop
├── Screens/               # One header per game screen (menu, gameplay, login, leaderboard, settings, etc.)
├── Assets/                # Sprites, textures, backgrounds
├── Fonts/                 # UI/score fonts
└── TextFiles/             # Save data: leaderboard scores/names + in-progress game state
```

## Notes

- Because save data is read/written relative to the working directory, always launch the executable from inside the `Orionis/` folder.
- Leaderboard and backup data live as plain text files under `TextFiles/` — feel free to inspect or reset them if you want a clean slate.
