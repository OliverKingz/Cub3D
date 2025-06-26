# Cub3D

<div align="right">

[![GitHub stars](https://img.shields.io/github/stars/OliverKingz/Cub3D?color=brightgreen)]()
[![Visits Badge](https://badges.pufler.dev/visits/OliverKingz/Cub3D)]()
[![Created Badge](https://badges.pufler.dev/created/OliverKingz/Cub3D)]()
[![Updated Badge](https://badges.pufler.dev/updated/OliverKingz/Cub3D)]()

</div>

[42-Cursus] A project inspired by the classic Wolfenstein 3D game. This ray-caster uses **MLX42 from Codam** to create a dynamic 3D maze navigable in first-person view, with textured walls, floor/ceiling colors, and smooth controls.

<div align="center">

![Example Gameplay](assets/images/Cub3D_GB.gif)

</div>

Keywords

- **Ray-Casting**
- **MLX42 from Codam**
- **3D Projection**
- **C Programming**
- **Game Development**

<div align="right">

Made by: [![Contributors Display](https://badges.pufler.dev/contributors/OliverKingz/Cub3d?size=30&padding=5&perRow=10&bots=true)](https://github.com/RaulPerezDEV)

</div>

---

## Index

- [Overview](#overview)
- [Features](#features)
- [Bonus Features](#bonus-features)
- [Requirements](#requirements)
- [How to Run](#how-to-run)
  - [Example Usage](#example-usage)
  - [Bonus Usage](#bonus-usage)
  - [Error Handling](#error-handling)
- [Controls](#controls)
- [What I Learned](#what-i-learned)
- [Assets Credits](#assets-credits)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

---

## Overview

**Cub3D** is a 3D maze exploration game built using ray-casting techniques, mimicking the mechanics of the iconic _Wolfenstein 3D_. The project leverages **MLX42** for rendering and emphasizes efficient mathematical algorithms to create a seamless first-person perspective. Players navigate a maze with textured walls, customizable floor/ceiling colors, and intuitive controls.

---

## Features

- **Ray-Casting Engine**: Dynamic 3D rendering from a 2D map.
- **Textured Walls**: Unique textures for North/South/East/West walls.
- **Customizable Colors**: RGB values for floor and ceiling.
- **Smooth Controls**: WASD movement, arrow-key rotation, and ESC to quit.
- **Map Validation**: Ensures maps are closed/surrounded by walls.

---

## Bonus Features

- **Minimap**: Displays a real-time top-down view of the maze.
- **Wall Collisions**: Prevents walking through walls.
- **Mouse Rotation**: Rotate the view by moving the mouse.
- **Animated Sprites**: Adds dynamic elements to the environment.
- **Doors**: which can open and close

---

## Requirements

- **MLX42** (provided by 42 or compiled from Codam).
- **Scene File**: Must be a valid `.cub` file (see [Example Usage](#example-usage)).

---

## How to Run

1. **Clone this repository:**

   ```bash
   git clone https://github.com/OliverKingz/Cub3D.git
   cd Cub3D
   ```

2. **Compile the project using the provided Makefile** (use the `bonus` rule for a better experience):

   For the mandatory part:

   ```bash
   make
   ```

   For the bonus part:

   ```bash
   make bonus
   ```

   If the above command fails to compile **MLX42** correctly (for example, on WSL or with specific compiler issues), you can use the alternative script to compile MLX42 library:

   ```bash
   bash alternative_mlx42_compiler.sh
   make bonus
   ```

3. **Run the game with a scene file** (e.g., `example.cub` for mandatory, `example_bonus.cub` for bonus):

   ```bash
   ./Cub3D assets/scenes/example.cub
   ./Cub3D_bonus assets/scenes/example_bonus.cub
   ```

---

### Example Usage

| **Command**                     | **Description**                 | **Expected Output**         |
| ------------------------------- | ------------------------------- | --------------------------- |
| `./Cub3D maps/valid.cub`        | Runs the game with a valid map. | Renders the 3D maze.        |
| `./Cub3D maps/invalid_open.cub` | Map not surrounded by walls.    | `Error: Map is not closed.` |

### Bonus Usage

Compile and run bonuses:

```bash
make bonus
./Cub3D_bonus assets/scenes/example.cub
```

| **Command**                               | **Description**       | **Expected Output**           |
| ----------------------------------------- | --------------------- | ----------------------------- |
| `./Cub3D_bonus assets/scenes/example.cub` | Displays the minimap. | Renders maze + top-down view. |

### Error Handling

| **Command**                        | **Error Scenario**    | **Output**                     |
| ---------------------------------- | --------------------- | ------------------------------ |
| `./Cub3D nonexistent.cub`          | Invalid file path.    | `Error: File not found.`       |
| `./Cub3D maps/missing_texture.cub` | Missing texture path. | `Error: Texture file missing.` |

---

## Controls

- **W/A/S/D**: Move forward/left/backward/right.
- **←/→ Arrow Keys**: Rotate view left/right.
- **ESC**: Close the window.
- **Mouse Move (Bonus)**: Rotate view horizontally.

---

## What I Learned

- **Ray-Casting Math**: Understanding angles, distances, and projections.
- **MLX42 Mastery**: Window management, event hooks, and image rendering.
- **Map Parsing**: Robust validation of user-provided files.
- **Optimization**: Balancing performance with real-time rendering.

---

## Assets Credits

- **Wall Textures**: Wolfenstein 3D (Id Software, 1992).
- **Torch Animation**: Original available at [OpenGameart](https://opengameart.org).
- **Door Texture**: Based on "LPC Door Rework" by AntumDeluge and Lanea Zimmerman (Sharm). Original available at [OpenGameart](https://opengameart.org/node/84409). This modified work is licensed under CC BY-SA 3.0.

---

## Authors

<div align="center">

| **Name**                   | **GitHub Profile**                              | **42 Login** |
| -------------------------- | ----------------------------------------------- | ------------ |
| **Oliver King Zamora**     | [OliverKingz](https://github.com/OliverKingz)   | **ozamora-** |
| **Raúl José Pérez Medina** | [RaulPerezDEV](https://github.com/RaulPerezDEV) | **raperez-** |

</div>

---

## Acknowledgments

This project is part of the **42 Cursus**, a rigorous programming curriculum that emphasizes hands-on learning and problem-solving. Special thanks to the 42 team for providing this challenging and rewarding project!  
Also thanks to peers and mentors for their feedback and support during the development process.

- **42 Community**: For the collaborative environment and peer reviews.
- **MLX42 Docs** for rendering guidance.
- **John Carmack & Romero** for pioneering ray-casting!
