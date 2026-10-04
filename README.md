# Sky Rescue

## Game Description

**Sky Rescue** is a 2D arcade-style helicopter rescue simulation created using the iGraphics library in C/C++. The player flies an emergency rescue helicopter to save stranded citizens from rooftops during floods and landslides, using a winch cable to hoist them up and a hospital helipad to drop them off.

The game was inspired by the recent floods and landslides in Chattogram, Bangladesh.

## Features

- Gravity-based helicopter flight with engine lift and smooth steering.
- Winch and hook system to rescue survivors from rooftops (up to 3 at a time).
- Fuel system with refueling at the base helipad and falling fuel cans.
- 3 lives system with a short shield after taking damage.
- 3 levels (Beginner, Intermediate, Expert), each with 3 sectors (Flood Basin, Mud & Landslide, Thunder Storm) – 9 sectors in total.
- Hazards: birds, eagles, falling rocks, drones, and lightning clouds.
- Rescue flares, Sky Blast EMP, and air-dropped medkits (life jacket and medkit box).
- Enemy helicopter battle in Sector 3.
- Pilot registration, top 5 high score leaderboard, and sound effects.
- Data saved in text files: `highscores.txt` (high scores) and `progress.txt` (pilot progress).

## Project Details

| Item | Details |
|---|---|
| IDE | Visual Studio 2010/2013 |
| Language | C, C++ |
| Platform | Windows PC |
| Genre | 2D arcade rescue simulation |
| Teamwork | GitHub and Gmail |

## How to Run the Project

Make sure you have the following installed:

- Visual Studio 2013
- MinGW Compiler (if needed)
- iGraphics Library (included in this repository)

### Steps

1. Open Visual Studio 2013.
2. Go to **File → Open → Project/Solution**.
3. Locate and select the `.sln` file from the cloned repository.
4. Make sure `enemy.png` and the other image files are in the project folder (or its `Images` folder).
5. Click **Build → Build Solution**.
6. Run the program by clicking **Debug → Start Without Debugging**.

## How to Play

### Controls

| Action | Keys |
|---|---|
| Lift up | Space / W / ↑ or hold Left Mouse Button |
| Move Left | A / ← |
| Move Right | D / → |
| Lower winch hook | Hold Q |
| Drop medkit | S / ↓ |
| Shoot flare | F / X |
| Sky Blast EMP | E |
| Pause / Resume | P |
| Back to menu | ESC |
| Retry (Game Over) | R |

## Game Rules

- The helicopter starts with 3 lives and 100% fuel.
- Hold **Q** above a survivor to lower the hook; the survivor is reeled in automatically.
- The helicopter carries a maximum of 3 survivors.
- Fly to the base helipad (left side) to drop them off, refuel, and restock medkits.
- Points:
  - 100 per survivor delivered
  - +150 bonus for 3 survivors delivered at once
  - +150 per medkit delivered
  - +60 per hazard shot
- Hitting a hazard, building, or the ground costs 1 life.
- The game ends when all lives are lost or fuel reaches 0.

## Levels and Rescue Quota

There are 3 levels and each level has 3 sectors (9 sectors in total).

| Level | Sector 1 | Sector 2 | Sector 3 |
|---|---:|---:|---:|
| Level 1: Beginner | 15 | 20 | 25 |
| Level 2: Intermediate | 20 | 25 | 30 |
| Level 3: Expert | 25 | 30 | 35 |

In Sector 3, meet the quota and destroy the enemy helicopter to win.

## Data Files

| File | Purpose |
|---|---|
| `highscores.txt` | Stores the top 5 pilot names and high scores. |
| `progress.txt` | Stores the pilot's progress (name, level, sector, score, total rescues and missions). |

## Project Contributors

1. **Hasibul Hasan Shuvo** – Flight physics, rendering, hazards, helipad landing, enemy helicopter
2. **MD. Fahim Talukder** – Image assets, menus, pilot registration, variables, leaderboard and data files, project integration
3. **Rafsan Sarker** – Survivor rescue and winch system, 3 lives, fuel system, HUD and sound

Teamwork was managed using GitHub (repository, branches, commits, pull requests) and Gmail (sharing files and coordination).

## Screenshots

### Menu

<img src="<img width="1079" height="606" alt="main_menu" src="https://github.com/user-attachments/assets/9bd60fe4-8df0-423c-a04b-feafb86a18d2" />
" width="300">

### Rescue Helicopter

<img src="<img width="1695" height="900" alt="rescue_helicopter" src="https://github.com/user-attachments/assets/8869f17a-a398-43d9-a41f-00d6b8b0cb82" />
" width="300">

### Enemy Helicopter

<img src=""<img width="1571" height="555" alt="enemy_helicopter" src="https://github.com/user-attachments/assets/deaa04ee-aa27-4308-ab51-22d9fbc8783b" />
 width="300">

## YouTube Link
**https://youtu.be/C7QLhoz5eTI?si=3GQegQg8oBvHWwER**

## Project Report

**Project Report: Sky Rescue**
