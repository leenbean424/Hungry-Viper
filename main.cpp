//=================================================================
// The main program file.
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// PROJECT INCLUDES
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "viper.h"

#include <math.h>
#include <stdio.h>

// Important definitions


/////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL VARS
Viper viper;

/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION PROTOTYPES
void playSound(char* wav);
int get_action(GameInputs inputs);
int update_game(int action);
void draw_upper_status();
void draw_lower_status();
void draw_border();
void draw_game(int draw_option);
void init_main_map();

/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION DEFINITIONS
/**
 * Program entry point! This is where it all begins.
 * This function is for all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */

  bool start_menu = true;
    void game_start_menu(GameInputs inputs) {
   
        uLCD.color(0xFFFFFF);
        uLCD.locate(5, 0);
        uLCD.printf("Welcome to Viper Game!");
        uLCD.locate(0, 3);
        uLCD.printf("Press B1 to start");
            if (!inputs.b1) {
                pc.printf("b1 pressed");
                uLCD.cls();
                start_menu = false;
            }
    
}
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    
    viper_init(&viper);
    
    // 0. Initialize the maps
    // TODO: implement maps_init() and init_main_map() function in map.cpp:
    maps_init();
    init_main_map();

    // Initialize game state
    set_active_map(0); // in map.cpp
    viper.head_x = viper.head_y = 5;

   

    while(start_menu == true) {
        GameInputs inputs = read_inputs();
        game_start_menu(inputs);
        }
    
    // Initial drawing
    draw_game(FULL_DRAW);
    
    
    // Main game loop
    while(1) {
        // Timer to measure game update speed
        Timer t;
        t.start();

        // 1. Read inputs 
        //TODO: implement read_inputs() function in hardware.cpp:
        GameInputs inputs = read_inputs();
        
        
        // 2. Determine action (move, act, menu, etc.)
        //TODO: implement get_action() function:
        int action = get_action(inputs);
        
        // 3. Update game
        //TODO: implement update_game() function:
        int result = update_game(action);

        uLCD.filled_rectangle(0, 0, 160, 7, BLACK);
        char str[1024];
        snprintf(str,sizeof(str),"Pos:%d,%d Score:%d",viper.head_x,viper.head_y,viper.score);
        uLCD.text_string(str,0,0,FONT_7X8,RED);

        // uLCD.filled_rectangle(128, 128, 160, 7, BLACK);
        char str1[1024];
        snprintf(str1, sizeof(str1),"Lives:%d, Invi:%d",viper.lives, viper.invincible);
        uLCD.text_string(str1, 0, 15,FONT_7X8,RED);

        
        // 3b. Check for game over based on result
        // and if so, handle game over
        if (result == GAME_OVER) { 
            draw_game(result);
            break;
        }
        //TODO: implement this here or as a new function.
        
        //      3b1. if game is over, then
        //      3b2. draw and display tezt for game over sign
                
        // 4. Draw screen -- provided.
        draw_game(result);
        
        // Compute update time
        t.stop();
        int dt = t.read_ms();

        // Display and wait
        // NOTE: Text is 8 pixels tall
        if (dt < 100) wait_ms(100 - dt);
    }
}

/**
 * Plays a .wav file
 */
void playSound(char* wav)
{
    // OPTIONAL: Implement
    
}

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8
#define MOVED 9
#define GOT_LENGTH 10
#define GOT_OBJ 11
#define INVINCIBILITY 12
#define VULNERABLE 13


int get_action(GameInputs inputs)
{
    // TODO: Implement
    
    // 1. Check your action and menu button inputs and return the corresponding action value
    
    if (!inputs.b1 && !viper.invincible) {
        return INVINCIBILITY;
    }
    if (!inputs.b1 && viper.invincible) {
        return VULNERABLE;
    }
    
    if (!inputs.b2) {
        return MENU_BUTTON;
    }
    // 2. Check for your navigation switch inputs and return the corresponding action value
    if (inputs.ns_up) {
        return GO_UP;
    }
    
    if (inputs.ns_down) {
        return GO_DOWN;
    }

    if (inputs.ns_right) {
        return GO_RIGHT;
    }

    if (inputs.ns_left) {
        return GO_LEFT;
    }

    if (inputs.ns_center) {
        return NO_ACTION;
    }
    // If no button is pressed, just return no action value
    return NO_ACTION;
}
//define adding length macros
#define  NOADD 0
#define  ADD1 1
#define  SUB1 2

bool invincibility = false; 
int freeze = 0;
int invCount = 0;
bool inverted = false;

void get_object(){
     int typeObject;
     if (get_here(viper.locations[0].x, viper.locations[0].y)-> type == TREAT) {
        pc.printf("got something!");
        viper.score++;
        viper.length++;
        typeObject = TREAT;

    } else if (get_here(viper.locations[0].x, viper.locations[0].y)-> type == BONK) {
        pc.printf("BONK!");
        viper.length++;
        typeObject = BONK;
    }

 }

int check_lives() {
    if (viper.lives == 0) {
        return GAME_OVER;
    } 
    return 0;
}



int turn_left() {

    if (viper.invincible== true) {
         for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_x = viper.head_x - 1;
          viper.locations[0].x = viper.locations[0].x - 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length-1; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length-1].x, viper.locations[viper.length-1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);
       
         return 0;
    } else if (get_west(viper.head_x, viper.head_y)->walkable == false) {
        viper.lives--;
        return check_lives();
    } else if (get_west(viper.head_x, viper.head_y)->type == FREEZE) {
        viper.frozen = true;
        viper.lives--;

    } else if (get_west(viper.head_x, viper.head_y)->type == SUPERSAYAN) {
        viper.invincible = true;
        invCount++;
    } else if (get_west(viper.head_x, viper.head_y)->type == VIPER_BODY) {
        viper.lives--;
        return check_lives();
    } else if (get_west(viper.head_x, viper.head_y)->type == TREAT) {
        viper.length++;
        viper.score++;

    }else if (get_west(viper.head_x, viper.head_y)->type == BONK) {
        viper.lives--;
        viper.length++;

    } else if (get_west(viper.head_x, viper.head_y)-> type == LIFE) {
        viper.lives++;
    } else if (get_west(viper.head_x, viper.head_y)-> type == INVERTED) {
        inverted = true;
    } else if (get_west(viper.head_x, viper.head_y)-> type == CHEST){
        viper.length--;
        viper.lives--;
     } else if (get_west(viper.head_x, viper.head_y)-> type == NONINVERT) {
         inverted = false;
         viper.score--;
    //  } else if (get_west(viper.head_x, viper.head_y)-> type == THEEND) {
    //      return GAME_OVER;
     }
    for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_x = viper.head_x - 1;
          viper.locations[0].x = viper.locations[0].x - 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length-1; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length-1].x, viper.locations[viper.length-1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);
       
         
         return check_lives();
}

int turn_right() {
    if (viper.invincible == true) {
        for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_x = viper.head_x + 1;
          viper.locations[0].x = viper.locations[0].x + 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length-1; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x,viper.locations[viper.length].y);
         
         
         return 0;
    if (get_east(viper.head_x, viper.head_y)->walkable == false) {
        viper.lives--;
        return check_lives();
        }
    } else if (get_east(viper.head_x, viper.head_y) -> type == VIPER_BODY) { 
        viper.lives--;
        return check_lives();
    } else if (get_east(viper.head_x, viper.head_y)->type == FREEZE) {
        viper.frozen = true;
        viper.lives--;
    } else if (get_east(viper.head_x, viper.head_y)->type == TREAT) {
        viper.length++;
        viper.score++;
    } else if (get_east(viper.head_x, viper.head_y)->type == SUPERSAYAN) {
        viper.invincible = true;
        invCount++; 
    }else if (get_east(viper.head_x, viper.head_y)-> type == BONK) {
        map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
        viper.lives--;
        viper.length++;
    } else if (get_east(viper.head_x, viper.head_y)-> type == LIFE) {
        viper.lives++;
    } else if (get_east(viper.head_x, viper.head_y)-> type == INVERTED) {
        inverted = true;
     } else if (get_east(viper.head_x, viper.head_y)-> type == CHEST){
        viper.length--;
        viper.lives--;
     } else if (get_east(viper.head_x, viper.head_y)-> type == NONINVERT) {
         inverted = false;
         viper.score--;
    //  } else if (get_east(viper.head_x, viper.head_y)-> type == THEEND) {
    //      return GAME_OVER;
    }
    for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_x = viper.head_x + 1;
          viper.locations[0].x = viper.locations[0].x + 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length-1; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x,viper.locations[viper.length].y);
         
         return check_lives();
}
int turn_up() {
    if (viper.invincible == true) {
        for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_y = viper.head_y - 1;
          viper.locations[0].y = viper.locations[0].y - 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);

         return 0;

    } else if (get_north(viper.head_x, viper.head_y)->walkable == false) {
        viper.lives--;
        return check_lives();
    } else if (get_north(viper.head_x, viper.head_y)->type == FREEZE) {
        viper.frozen = true;
        viper.lives--;
    } else if (get_north(viper.head_x, viper.head_y) -> type == VIPER_BODY) { 
        viper.lives--;
        return check_lives();
    } else if (get_north(viper.head_x, viper.head_y)->type == SUPERSAYAN) {
        viper.invincible = true;
        invCount++;
    } else if (get_north(viper.head_x, viper.head_y)->type == TREAT) {
        viper.length++;
        viper.score++;
    } else if (get_north(viper.head_x, viper.head_y)-> type == BONK) {
        map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
        viper.lives--;
        viper.length++;
    } else if (get_north(viper.head_x, viper.head_y)-> type == LIFE) {
        viper.lives++;
    } else if (get_north(viper.head_x, viper.head_y)-> type == INVERTED) {
        inverted = true;
    } else if (get_north(viper.head_x, viper.head_y)-> type == CHEST){
        viper.length--;
        viper.lives--;
     } else if (get_north(viper.head_x, viper.head_y)-> type == NONINVERT) {
         inverted = false;
         viper.score--;
    //  } else if (get_north(viper.head_x, viper.head_y)-> type == THEEND) {
    //      return GAME_OVER;
      }
    for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_y = viper.head_y - 1;
          viper.locations[0].y = viper.locations[0].y - 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);
         
         return check_lives();
            
}

int turn_down() {
    if (viper.invincible == true) {
       for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_y = viper.head_y + 1;
          viper.locations[0].y = viper.locations[0].y + 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);
        
         return 0;

    } else if (get_south(viper.head_x, viper.head_y)->walkable == false) {
        viper.lives--;
        return check_lives();
    }if (get_south(viper.head_x, viper.head_y) -> type == VIPER_BODY) { 
        viper.lives--;
        return check_lives();
    } else if (get_south(viper.head_x, viper.head_y)->type == FREEZE) {
        viper.frozen = true;
        viper.lives--;
    } else if (get_south(viper.head_x, viper.head_y)->type == SUPERSAYAN) {
        viper.invincible = true;
        invCount++;
    } else if (get_south(viper.head_x, viper.head_y)->type == TREAT) {
        viper.length++;
        viper.score++;
    } else if (get_south(viper.head_x, viper.head_y)-> type == BONK) {
        viper.lives--;
        map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
        viper.length++;
        
    } else if (get_south(viper.head_x, viper.head_y)-> type == LIFE) {
        viper.lives++;
    } else if (get_south(viper.head_x, viper.head_y)-> type == INVERTED) {
        inverted = true;
     } else if (get_south(viper.head_x, viper.head_y)-> type == CHEST) {
        viper.length--;
        viper.lives--;
     } else if (get_south(viper.head_x, viper.head_y)-> type == NONINVERT) {
         inverted = false;
         viper.score--;
    //  } else if (get_south(viper.head_x, viper.head_y)-> type == THEEND) {
    //      return GAME_OVER;
      }
    for (int i = viper.length; i > 0; i--) {
            viper.locations[i].x = viper.locations[i - 1].x;
            viper.locations[i].y = viper.locations[i - 1].y;   
          }
          
          viper.head_y = viper.head_y + 1;
          viper.locations[0].y = viper.locations[0].y + 1;
          add_viper_head(viper.locations[0].x, viper.locations[0].y);

          for (int i = 1; i < viper.length; i++) {
              add_viper_body(viper.locations[i].x, viper.locations[i].y);
          }
         add_viper_tail(viper.locations[viper.length - 1].x,viper.locations[viper.length - 1].y);
         map_erase(viper.locations[viper.length].x,viper.locations[viper.length].y);
         remove_viper_tail(viper.locations[viper.length].x, viper.locations[viper.length].y);
         
         return check_lives();
}




int update_game(int action) {
    viper.head_px = viper.head_x;
    viper.head_py = viper.head_y;

    if (action != NO_ACTION) {
        print_map();
    }

    if (action == INVINCIBILITY) {
        viper.invincible = true;
    }

    if (action == VULNERABLE) {
        viper.invincible = false;
    }
    if (viper.frozen == true) {
        if (freeze < 50) {
        freeze++;
        return 0;
        }
    freeze = 0;
    viper.frozen = false;
    }
    if (viper.invincible == true && invCount > 0) {
        if (invCount > 30) {
            viper.invincible = false;
        } else {
            invCount++;
        }
    }

    
    if (action == GO_LEFT) {
        if (inverted == true) {
            if (turn_right() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    } else if (turn_left() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    }

    if (action == GO_RIGHT) {
        if (inverted == true) {
            if (turn_left() == GAME_OVER) {
                draw_game(GAME_OVER);
                return GAME_OVER;
            }
        } else if (turn_right() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    }

    if (action == GO_UP) {
        if (inverted == true) {
            if (turn_down() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    } else if (turn_up() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    }

     if (action == GO_DOWN) {
        if (inverted == true) {
            if (turn_up() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
            }
        } else if (turn_down() == GAME_OVER) {
            draw_game(GAME_OVER);
            return GAME_OVER;
        }
    }

    if (viper.length > VIPER_MAX_LENGTH) {
        return GAME_OVER;
    }

    return 0;
}

// void game_start_menu(GameInputs inputs) 
// {
   
//         uLCD.color(0xFFFFFF);
//         uLCD.locate(5, 0);
//         uLCD.printf("Welcome to Viper Game!");
//         uLCD.locate(0, 3);
//         uLCD.printf("Press B1 to start");
//             if (!inputs.b1) {
//                 pc.printf("b1 pressed");
//                 uLCD.cls();
//                 start_menu = false;
//             }
    
// }
/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(  0,   9, 127,  14, WHITE);   // Top
    uLCD.filled_rectangle(  0,  13,   2, 114, WHITE);   // Left
    uLCD.filled_rectangle(  0, 114, 127, 117, WHITE);   // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE);   // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */

 //takes in result from draw_game
void draw_game(int draw_option)
{
    // Draw game border first
    
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        int u = 58;
        int v = 56;
        draw_viper_head(u, v);
        draw_viper_body(u-11, v);
        draw_viper_tail(u-22, v);
        return;
    }

    if (draw_option == GAME_OVER) {
        for (int i = -5; i <= 5; i++) {
            for (int j = -4; j <= 4; j++) {
                int u = (i + 5) * 11 + 3;
                int v = (j + 4) * 11 + 15; 
                draw_nothing(u,v);
            }
        }
        char str[1024];
        char str2[1024];
        snprintf(str, sizeof(str), "  GAME OVER ");
        snprintf(str2, sizeof(str2), "   Score: %d", viper.score);
        uLCD.text_string(str, 1, 7, FONT_7X8, RED);
        uLCD.text_string(str2, 1, 9, FONT_7X8, 0xD2691E);
        return;
    }


    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + viper.head_x;
            int y = j + viper.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + viper.head_px;
            int py = j + viper.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
                        
        
        
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
            
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                        
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
                
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" treats
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_treat(i % map_width(), i / map_width());
    }
    pc.printf("Treats added!\r\n");

    // "Random" Bonk
     for(int i = map_width() + 2; i < map_area(); i += 32) {
        add_bonk(i % map_width(), i / map_width());
    }

    // draw_bonk(44, 15);
    pc.printf("Bonk added\r\n");

    for(int i = map_width() + 4; i < map_area(); i += 90) {
        add_life(i % map_width(), i / map_width());
    }
    pc.printf("Life added\r\n");

    for(int i = map_width() + 9; i < map_area(); i += 63) {
        add_freeze(i % map_width(), i / map_width());
    }
    pc.printf("Freeze added\r\n");

    for(int i = map_width() + 5; i < map_area(); i += 213) {
        add_supersayan(i % map_width(), i / map_width());
    }
    pc.printf("Supersayan added\r\n");

   for(int i = map_width() + 9; i < map_area(); i += 142) {
        add_inverted(i % map_width(), i / map_width());
    }
    pc.printf("Inverted added\r\n");

    for(int i = map_width() + 13; i < map_area(); i += 91) {
        add_noninvert(i % map_width(), i / map_width());
    }
    pc.printf("Noninverted added\r\n");

    for(int i = map_width() + 13; i < map_area(); i += 42) {
        add_chest(i % map_width(), i / map_width());
    }
    pc.printf("Chest added\r\n");

    // for(int i = map_width() + 9; i < map_area(); i += 25) {
    //     add_theend(i % map_width(), i / map_width());
    // }
    // pc.printf("the end added\r\n");

    
   


    // adds walls
    pc.printf("Adding walls!\r\n");
    add_wall(            0,              0, HORIZONTAL, map_width());
    add_wall(            0, map_height()-1, HORIZONTAL, map_width());
    add_wall(            0,              0,   VERTICAL, map_height());
    add_wall(map_width()-1,              0,   VERTICAL, map_height());
    pc.printf("Walls done!\r\n");
    
    add_viper_head(viper.locations[0].x, viper.locations[0].y);
    add_viper_body(viper.locations[1].x, viper.locations[1].y);
    add_viper_tail(viper.locations[2].x, viper.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30,  0,   VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39,  0,   VERTICAL, 10);
    pc.printf("Added!\r\n");
    
    print_map();
}


