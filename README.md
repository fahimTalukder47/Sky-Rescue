# Sky Rescue

## 1. Game Description
**Sky Rescue** is a 2D side-scrolling helicopter simulation and rescue game inspired by disaster relief operations in Chattogram, Bangladesh. Players control an elite rescue pilot navigating a helicopter through treacherous environments to save stranded civilians. The game features three escalating difficulty sectors (Flood Basin, Mudslide, and Thunderstorm), resource management (fuel and passenger capacity), and an intense final boss fight against a rogue aircraft.

## 2. Project Details
The primary objective of this project is to develop an interactive, engaging, and fully playable 2D game using the C++ programming language and the iGraphics library. 
* **Target Gameplay Duration:** Minimum 10-15 minutes to complete all sectors.
* **Core Loop:** Fly, rescue civilians, return to the hospital helipad to drop them off and refuel, and survive environmental hazards.
* **Theme:** Disaster relief, tactical flight simulation, and heroic rescue operations.

### Key Features
* **Advanced 3-Lives System:** Players have 3 lives instead of 1-hit deaths. Crashing or taking damage triggers a bounce-back mechanic and temporary invulnerability (blinking effect).
* **Boss Fight (Rogue Storm Zephyr):** A challenging Sector 3 encounter featuring a boss with a health bar, horizontal patrol AI, and plasma projectiles. The player can defeat the boss using flares/EMP.
* **Dynamic Resource Management:** Real-time tracking of fuel consumption and maximum passenger capacity.
* **Custom UI & HUD:** Image-based graphical UI tracking lives (hearts), fuel bars, and capacity load.
* **Persistent Career Progression:** The game automatically saves career rescue counts and unlocked sectors using a local text file.
* **Procedural Hazards:** Dynamically generated flocks of birds, random building heights, and environmental obstacles.


## 3. Technical Architecture
The project is built using a modular C++ architecture to separate concerns and maintain clean code.
* **Language:** C++
* **Graphics Library:** iGraphics (A lightweight wrapper over OpenGL and GLUT)
* **File Structure:**
  * `iMain.cpp`: Application entry point, iGraphics initialization, and event callbacks.
  * `Variables.h`: Global state management, data structures for the player, enemies, and UI.
  * `Rendering.h`: All drawing logic (menus, HUD, environment, sprites).
  * `Physics.h`: Collision detection, flight dynamics, and frame-by-frame updates.
  * `Rescue.h`: Logic for spawning civilians, hoisting mechanics, and dropping them off.
  * `Hazards.h`: Enemy AI (birds, Boss logic) and obstacle generation.
  * `Menu.h`: Menu navigation, input boxes, and screen state transitions.
  * `Leaderboard.h`: File I/O operations for saving and loading player progress.

## 4. How to Run the Project
**Prerequisites:** Microsoft Visual Studio or a compatible C++ IDE with iGraphics/OpenGL configured.

1. Open the project folder
2. Open the Visual Studio Solution file (`.sln`).
3. Ensure the linker settings are properly configured with the standard iGraphics dependencies:
   * `opengl32.lib`, `glu32.lib`, `glut32.lib`
4. Build the solution (Shortcut: `Ctrl + Shift + B`).
5. Run the executable (Shortcut: `F5`).

## 5. How to Play
### Controls
* **Mouse Movement:** Steer the helicopter. Move the mouse smoothly to guide the aircraft.
* **Left Mouse Button:** Click UI buttons in the menu / Deploy flares during the Boss fight.
* **Spacebar:** Lower the rescue hoist to pick up survivors from buildings.
* **ESC Key:** Pause the game / Return to the main menu.

## 6. Game Rules
1. **Rescue Quotas:** You must rescue a specific number of civilians to complete each sector and unlock the next one.
2. **Fuel Limitation:** Flying drains fuel. Return to the Hospital Helipad to refuel before hitting zero.
3. **Weight Limit:** Your helicopter can only carry a maximum number of passengers at a time. Drop them off at the Hospital to free up space.
4. **Avoid Hazards:** Hitting buildings, birds, or enemy projectiles will cost you 1 life. 
5. **Survival:** You have a maximum of 3 lives per run. Losing all 3 lives results in a Game Over.
6. **Victory Condition:** Reach Sector 3, survive the thunderstorm, and deplete the Boss's health bar to zero to win the game.


## 7. Project Contributors
* **[MD Fahim Talukder / 00725105101056]** 
* **[Hasibul Hasan Shuvo / 00725105101030]** 
* **[Rafsan Sarker / 00725105101055]** 
