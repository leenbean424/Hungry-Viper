### Hungry-Viper ###

# Overview #
This is a modified version of the classic Snake game. All development was done in the online Mbed compiler. The objective was to create a C++ game with graphics designed to run on mbed LPC1768 microcontroller with a uLCD-144-G2 screen with buttons and a 5-way nav switch for controls. 
# Main Elements # 
These are the major elements that make up the functionality of the game.
1. Graphics: The viper moves on a 11x11 screen with game tiles that update with every viper movement. Only one column or row of the map is updated for memory optimization. A game object - or a sprite - can be stored on one tile at a time. 
2. Hash_table: A Hash Table using an external chaining resolution strategy stores game elements
3. Hardware: Code implementation for hardware is required to interact with a piezo speaker, 4 buttons, the uLCD, and the navSwitch. 

# Main Features # 
These are the major features in the game that the code exhibits. Many of these are eatable map items that affect the viper's gameplay conditions. 
- Lives: The viper has multiple lives displayed on the screen and sprites in the game can increase or decrease the amount of lives the viper has. 
- Inversion: After eating a certain sprite, the viper movement will be inverted. 
- Invincibility: If the viper has an invincibility status is striggered, the viper is unaffected by any features of the game.
- Frozen game: Any input while the game is frozen will not affect the game functionality. 
 



