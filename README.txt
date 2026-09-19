SKY RESCUE - ENEMY HELICOPTER FINAL HUD VERSION

Changes in this version:
1. Sector 3 uses the supplied enemy.png as the enemy helicopter.
2. Enemy helicopter main and tail rotors are drawn procedurally and animated.
3. Sector 3 buildings are kept lower.
4. Fuel HUD uses the supplied battery-style image as the frame.
5. Fuel/stamina fill is drawn INSIDE the battery frame (green at normal fuel).
6. Removed the unnecessary outer box around the enemy helicopter HP display.
7. Enemy HP text and red HP bar are displayed above the enemy helicopter.
8. imgBoss is defined in iMain.cpp to prevent LNK2001.

Place all image files in the executable working directory, or use the Images folder as supported by the source code.
Build with Visual Studio using Build -> Rebuild Solution.
