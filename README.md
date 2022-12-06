# Hungry-Viper
The goal of this project is to build a modified version of an interactive game called Hungry Viper on the
Mbed platform. The game is like the classic Snake game. In this project, you will build a handheld Hungry
Viper game using the gaming circuit constructed during HW3 and your hash table implementation from
P2-1.
In your Hungry Viper game, you will be controlling a viper. The character movement of the viper will be
controlled using the nav-switch. The buttons will be used to trigger actions in the game. Crucially, the map
area of the game will be much larger than the area you are able to display on the screen. Objects on the map
will be stored in a hash table, and you will look up their correct locations to display them at every game
update.
There are several basic features that your game must implement in order to receive baseline credit; advanced
features are an opportunity to earn full and possibly extra credit. The list of basic features and examples of
some advanced features are given below.
Please note that the game features, art, and actions available in the game are intentionally vague, and the
specific design of the game is up to your creativity. Games can be extremely varied, and this project is an
opportunity for you to make something unique. HAVE FUN WITH IT!
Viper Motion & The Map
The Viper in the game moves around in the direction pressed on the nav-switch. The Viper is a struct
that holds an array of coordinates, along with other information. The Map for your game is the world that
the head of the Viper moves around in. The Map is made up of individual tiles, and a grid of 11 x 9 tiles is
displayed on the screen at any time. The head of the Viper is always displayed in the center of the screen.
The Map should be at least 50 x 50 tiles and should have walls around the edges to prevent the Viper from
leaving the map. The Viper dies when it bumps into the walls, and this ends the game.
You will need to populate the Map with Items relevant to your game - these Items can include scenery,
walls, objects, mud, etc. Please note that the Viper object itself is not a Map Item. Implementation details
for the Map are discussed in detail in the technical reference section of this document, below.
ECE 2035: Project 2-2
Page 2 of 8
The Goal
The crux of this game, as with all versions of the game of inspiration (Snake), is to gain as many points as
possible! The player must keep eating items that could gain points while keeping the Viper alive. The game
consists of the following steps.
1. Start the game somewhere on the map (your choice). The initial Viper length is three, and there
should be point-gaining objects scattered on the map.
2. Search for objects that could boost-up the Viper (making it have increased abilities, like temporarily
resilient or invincible) and avoid objects that could boost-down the Viper (making it have reduced
abilities, like, unable to gain points).
3. As your score increases, the speed and length of the Viper should also increase to make the game
more difficult.
4. You will need to keep track of all the positions on the map that belong to the Viper to update the
map correctly.
5. Gain as many points as possible before the Viper reaches its maximum length or hits something
that is not walkable.
6. After reaching maximum length or hitting something that is not walkable, display a game over
screen and end the game. Note that all parts of the Viper are considered not walkable!
Graphics
You should put some effort into making your game look good! At least one sprite is required as a basic
feature. You have more opportunities to design and use multiple sprites for advanced features. A sprite in
this context is a tile that’s more than just a rectangle. You should be using the draw_img(…) or
uLCD.BLIT(…) functions to accomplish this.
A status area is set aside at both the top and bottom of the screen. The top status area should display at a
minimum the current Viper head coordinate within the map. These areas can also be used to show
information such as current score, current speed, current boost modes (ups, downs), and so on.
Basic Feature Summary
These features are for baseline credit and constitute a functional, but minimal, Viper game.
1. Nav-switch moves the Viper.
2. Game over: End game and display a game over screen when Viper reaches its maximum length or
hits something that is not walkable.
3. The map must be bigger than the screen (at least 50 x 50 tiles).
4. The Viper grows when it eats an item.
5. Have map items that could boost-up (temporarily make the game easier for the player) or boostdown (temporarily make the game harder for the player) the Viper - at least 1 boost-up and 1 boostdown items. An example of a boost-up is to allow the Viper, after eating a special map item, to hit
something that is not walkable and survive; it just stops the Viper from moving in that direction but
does not end the game. An example of a boost-down is a poisonous object that when eaten prevents
the Viper from gaining points for a little while.
ECE 2035: Project 2-2
Page 3 of 8
6. Status bar shows Viper head coordinates.
7. Art includes at least one sprite.
8. Invincibility button: temporarily turns on all boost-up features that protect the Viper from dying
(w/out having to make the Viper take some action). This is helpful in testing and demonstrating
your features, particularly if you are not skilled with maneuvering your Viper and tend to hit things
like walls that are not walkable. It’s frustrating for that to end your game while testing/demoing.
Advanced Feature Examples
Advanced features in this project are open ended and allow you to make the game your own. The features
listed below are all acceptable, but this is not an exhaustive list. Each extra feature is worth +5 points, and
you must tell your grader before the demo begins which extra features you used. Other features that are at
or above the difficulty level of those listed here are acceptable but must be approved by an instructor or
graduate TA: there will be a pinned discussion topic on Ed Discussion to confirm extra features. If you
intend to use features that aren’t listed here, start a follow-up on this discussion thread to clear it with the
GTAs or instructors before grading begins.
• Game state management: Have a pause game button enable to pause and resume the game.
• Additional boost-up/down Map Items: Have different kinds of boost-ups/downs object in Map
that takes effect temporarily upon interaction with Viper.
o Sticky joystick which makes Viper continuously move in the direction last directed
o An object that could lower speed for the Viper (consider it as a boost-up)
o Magnet that allows the Viper to attract other objects
o Objects that give negative effects like speed up or extra length without score.
Note: Each kind of object can be counted as a feature
• Difficulty modes: Have different difficulty levels that the player could choose from. The modes
should have different speed options and maximum length to reach.
• Game start page: Create a Game start page that allows the player to choose various settings, like
game mode, past scores, etc.
• Random map initialization: Randomly select the locations of objects when the game starts, so
every time the game starts, the objects are in different locations. (Hint: seed the random number
generator on button push event times.)
• Sound effects: You can have background music & interaction sounds.
ECE 2035: Project 2-2
Page 4 of 8
• Pathway to another map: Have a second map that you could enter from the main map through a
“wormhole.” (Maybe when the Viper interacts with a specific type of object). You could have some
special objects awaiting the Viper in the second map.
• Moving objects: Have special types of objects that can change positions under their own control
as game updates or trigger events.
• Sprites: Have 8 or more additional objects represented with sprites to make your game look
awesome. Check out https://www.piskelapp.com to make your sprites that you can import and draw
on the screen using the draw_img(…) or uLCD.BLIT(…) methods.
• Animation: Animation for interactions with things in the map (e.g., crumbs spraying out when
something is eaten).
• In-game menu:
o Save the game
o Show status information
o Configuration (button mapping)
• Multiple lives and the possibility to lose and start over:
o Health & stuff that hurts you.
o Spikes, enemies, etc.
• Save the game: Being able to save game (persistent over a power-off event)
P2-2 Technical Reference
In this project, you’ll be combining hardware interface libraries for an LCD screen, pushbuttons, navswitch, and possibly the speakers and an SD card reader into a cohesive game. The shell code has several
different modules. This document is intended to be a reference for various technical considerations you’ll
need when implementing your game.
Hash Table
The game will make use of your HashTable library, implemented in P2-1. In order to use this library within
the Mbed environment, the easiest strategy is to simply copy and paste the code into the correct files. The
shell project has two files already for this purpose: hash_table.cpp and hash_table.h. Copy your completed
code from P2-1 into these files before starting anything else. Then implement the functions in map.cpp to
create and access the HashTable used to implement the map functions (as described in the Map Module
section below). When you first import the shell code, before you add your HashTable implementation, the
shell code will compile, but the game screen will only show a green rectangle. Once you add your
HashTable code and implement the map functions in map.cpp, it will look more interesting.
ECE 2035: Project 2-2
Page 5 of 8
USB Serial Debug
Debugging is an important part of any software project and dealing with embedded systems can make
debugging difficult. Fortunately, there is a built-in serial monitor on the Mbed that allows you to see printfstyle output from the Mbed on your computer. The tutorial to set that up can be found here:
https://os.mbed.com/handbook/SerialPC
For Windows users, please refer to https://os.mbed.com/handbook/Windows-serial-configuration on more
information on configuring Serial PC. For MAC/Linux users, this process is a bit more baked in. Please
refer here for necessary information: https://os.mbed.com/handbook/Mac-or-Linux-terminals.
The Serial PC object described in the tutorial is already set up for you in globals.h, so you won’t need to
declare it again. Any file that includes this header can print to the USB like so:
pc.printf(“Hello, world!\r\n”);
Please, note that in globals.h a F_DEBUG flag is defined and set. You can use this flag to run your game in
debug mode if it is set (1), or normal mode if it is reset (0). You can also use it to guard your printf(…)
statements and toggle them off or on.
Game Loop Overview
The basic structure for organizing a video game is called the game loop. Each iteration of this loop is known
as a frame. At each frame, the following operations are performed, typically in this order:
1. Read inputs
2. Update game state based on the inputs
3. Draw the game
4. Frame delay
You’ll be implementing parts of each of these steps. The game loop shell code (with timing already
implemented) is in main.cpp. Comments included in the game loop indicate what you need to implement.
Refer to .h files for specification and documentation of functions. Be sure to add documentation for the
code you write.
Read Inputs. Reading user input for a frame happens only once during the frame. This serves two purposes.
For one, it isolates the part of the code that has to deal with the input hardware to just the read_inputs
function, allowing the rest of the code to deal with only the results of the input operation. Secondly, it
ensures a constant value of the “true” input for a particular frame. If there are multiple parts of your game
update logic that have to interact with the inputs, it is convenient to know that these inputs are guaranteed
to be the same.
Update game. This is where the magic happens. Based on the current state of the game -- where the Viper
is, whether it a boost-up/boost-down is in effect, what other objects are nearby -- you compute what the
next state should be, based on the inputs you’ve already measured. For example, if the accelerometer is
tilted toward the top of the screen, the Viper should move up in the map. This is where most your
development will be focused.
ECE 2035: Project 2-2
Page 6 of 8
Draw game. With the state updated, you now need to show the user what changed by drawing it to the
screen. This step is discussed in much more detail below, but for now you’ll want to know that the entry
point to this portion of the code is called draw_game.
Frame delay. By default, loops in C run as fast as the instructions can possibly execute. This is great when
you’re trying to sort a list, but it’s really bad for games! If the game updates as fast as possible, the user
might not be able to understand what’s happening or control the character appropriately. So, we introduce
a delay that aims to make each frame take 100ms. The time for all the proceeding 3 steps is measured, and
the remaining time is wasted before starting again. If more than 100ms has already passed, no additional
delay is added. As you’re developing your game, be careful that your frames don’t get too long, or the feel
of your game will degrade.
Map Module
In order to think about updating the game state (moving the player) and drawing the screen, we first need
some way to represent the world. This module accomplishes that task.
The map is a two-dimensional grid whose origin is at the top-left corner of the world. The X coordinate
increases toward the right, and the Y coordinate increases toward the bottom. This left-handed coordinate
system is chosen for consistency with the graphics; see that section for more details. The finest granularity
of the map is a single grid cell; the player moves from cell to cell, and each cell contains at most one
MapItem. If the cell is empty, then that cell is free space on the map.
The map in this game is represented by a collection of MapItems held in a HashTable. The keys in the
HashTable are (x,y) pairs. The data in the HashTable are all of type MapItem, defined in map.h. So, for
example, if you access the key “(10, 23)” in the HashTable and the data is a MapItem whose type is WALL,
then the Viper should not be able to walk into that cell.
The shell code is written so that the use of the HashTable is hidden inside the map module; that is, the
hash_table.h is only included from map.cpp, and the HashTable functions are only used internally to that
module. The public API of the map module does not expose the HashTable since this is an implementation
detail of the map and does not affect the rest of the game. This hides the complexity of the HashTable
(questions like “what is the best hash function?” and “how do I map (x,y) pairs into integer keys for use in
my hash table?”) within the map module itself and simplifies the rest of the game logic.
The public API for the map module is provided in map.h. All functions and structures are documented
there. There are functions for accessing items in the map (e.g., get_here, get_north), modifying the map
(e.g. add_wall), and selecting the active map. You are encouraged to add more functionality to this API as
you deem necessary for your game. The point of an API is to be useful to the programmer; if these functions
are insufficient, add more!
Map Items. This is the basic unit of the map and is the underlying type of all the void* data in the map
HashTable. Each MapItem has an integer field, called “type” which tells you what kind of item it is. This
allows you to store different information in the map, such as the location of walls and the location of trees,
using the same data structure. Each MapItem also has a function pointer of type DrawFunc, that will draw
that MapItem. Its inputs are a pixel location (u,v) of the tile. Finally, each MapItem has two additional
parameters: an integer flag, walkable, that describes if the Viper is allowed to walk on that cell; and a void*
ECE 2035: Project 2-2
Page 7 of 8
data for storage of any extra data required during the game update. Walls probably don’t need extra data;
other items such as muddy spots, oil slicks, doors, or wormholes might.
Two-dimensional keys. As you implemented in P2-1, the HashTable accepts only unsigned integers as
keys. However, for this application you need to use two integers (the X & Y coordinates) as the key. In
order to do this, you need to have a function to map these coordinates unambiguously into a single integer.
This function is called XY_KEY, and is private to map.cpp. You then also need a hash function that will
take this key as normal and produce a hash value for bucket selection in the HashTable.
The Active Map. All operations in the Map API use the “active map.” In the shell code, there is only one
active map. The function get_active_map returns this map, and the function set_active_map does nothing.
You may modify these to allow selection between multiple maps. Once an active map is selected using
set_active_map, all other functions (accessors and modifiers) will use the currently active map. Only one
map can be active at a time; setting a new active map implicitly deactivates the previous active map.
Graphics
The graphics module houses most of the drawing code for the game. This includes all the drawing functions
for the various MapItems. The entry point for drawing the screen is the draw_game function. This section
describes how that function accomplishes drawing the tiles, and various ideas to consider as you extend this
function for your own game.
Coordinate Reference Frames. There are several relevant coordinate frames for this game. The first we
have already covered: the map frame. This frame’s coordinates are labeled (x,y) and its origin is the top
corner of the map. X increases right, and Y increases down. All frames in the game are this left-handed
orientation.
The next frame is the local drawing frame. This frame is centered on the Viper, and ranges from (-5,-4) to
(5,4), i.e. it is an 11x9 grid of cells. This frame is iterated in draw_game and each cell is drawn in turn using
ECE 2035: Project 2-2
Page 8 of 8
the DrawFunc from the map, or a draw_nothing function if there is no MapItem. The coordinates of this
frame are labeled (i, j).
Finally, there are the pixels on the screen. This frame has its origin at the top-left corner of the screen. The
screen is a 128x128 array of pixels. The coordinates of this frame are labelled (u,v). Each cell in the map is
11x11 pixels.
Drawing functions. As noted above, each MapItem has an associated DrawFunc that knows how to draw
that item. These functions take as input a (u,v) coordinate for the top-left pixel of the tile, and draw an
11x11 image that represents the MapItem. An example is the draw_wall function, in graphics.h.
You will need to add more draw functions as you add more types of MapItem. You are free to implement
these in whatever way you like, using the full power of the uLCD library. However, a simple way to do this
has been given to you. The draw_img function takes a string of 121 (= 11 * 11) characters, each representing
a pixel color, and translates that into a BLIT command to draw those colors to the screen. You can use this
function to make nice graphics very simply by defining a new string that represents the image you want to
draw. This is the recommended method for generating art for your game.
Drawing Performance. The screens are notoriously slow to draw, and the length of time it takes to
complete a drawing command is proportional to the number of pixels that it changes on the screen. So, the
drawing code goes through some hoops to make sure that things keep moving quickly. In particular, the
drawing code requires not only the current Viper position (Viper.head_x and Viper.head_y) but also the
previous position (Viper.head_px and Viper.head_py), in order to determine what has changed on the
screen. If an element on the screen has not changed, it is not redrawn. This saves time and makes the game
update more quickly. You’ll need to be careful with this as you decide how many items to put in your map
and how to draw the new items you add.

