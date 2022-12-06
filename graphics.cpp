// ============================================
// The Graphics class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "graphics.h"

#include "globals.h"

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = 0xFFFF00;   // Yellow
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = 0xD2691E;   // "Dirt"
        else if (img[i] == '5') colors[i] = LGREY;      // 50% grey
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'B') colors[i] = BROWN;
        else if (img[i] == 'T') colors[i] = 0X30D5C8;  // turquoise
        else if (img[i] == 'W') colors[i] = 0XFFFFFF;  // white
        else if (img[i] == 'L') colors[i] = 0X9284C2;  // lavender
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_wall(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    const char* img = 
    "T T T T T T"
    " T T T T T "
    "T T T T T T"
    " T T T T T "
    "T T T T T T"
    " T T T T T "
    "T T T T T T"
    " T T T T T "
    "T T T T T T"
    " T T T T T ";
    draw_img(u, v, img);
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    
    // pc.printf("Drew wall!");
}

void draw_plant(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_chest(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    uLCD.filled_rectangle(u, v, u+10, v+10, BLUE);
}

void draw_treat(int u, int v) {
   
    const char* img = 
    "      GGGG "
    "       GGG "
    "      GGG  "
    " BRRRRRRRB "
    "BRRRRRRRRRB"
    "BRRRRRRRRRB"
    "BRRRRRRRRRB"
    " BRRRRRRRB "
    "  BRRRRRB  "
    "   BBBBB   ";
    draw_img(u, v, img);
    pc.printf("treat drawn\r\n");
     
}

void draw_bonk(int u, int v) { 
    const char* img = 
    "WWWWWW     "
    "WBBBBW     "
    "WBBBBW     "
    "WBBBBW     "
    "WBBBBW     "
    "WBBBBW     "
    " WBBW      "
    " WRRW      "
    " WRRW      "
    " WBBW      "
    " WBBW      ";
    draw_img(u, v, img);
    pc.printf("bonk drawn\r\n");
}

void draw_life(int u, int v) {
     const char* img = 
    "           "
    "  W     W  "
    " WRW   WRW "
    "WRRRWWWRRRW"
    "WRRRRRRRRRW"
    " WRRRRRRRW "
    "  WRRRRRW  "
    "   WRRRW   "
    "    WRW    "
    "     W     " 
    "           ";

    draw_img(u, v, img);
    pc.printf("life drawn\r\n");
}

void draw_freeze(int u, int v) {
    const char* img = 
    "   WWWWW   "
    " WWBBWBBWW " 
    "  WWWWWWW  "
    "   WWWWW   "
    "     W     "
    " WWWWWWWW  "
    "WWWWWWWWWWW"
    "WWWWWWWWWWW"
    "WWWWWWWWWWW" 
    " WWWWWWWWW "
    "   WWWWW   ";

    draw_img(u, v, img);
    pc.printf("freeze drawn\r\n");
}

void draw_supersayan(int u, int v) {
    const char* img = 
    "    WYW    "
    "   WYYYW   "
    "  WYYYYYW  "
    "WYYYYYYYYYW"
    "  WYYYYYW  "
    "WYYYYWYYYYW"
    "WYYW   WYYW" 
    "wYW     WYw"
    " W        W"
    "           "
    "           ";

    draw_img(u, v, img);
    pc.printf("supersayan drawn\r\n");
}

void draw_inverted(int u, int v) {
    // const char* img = 
    // "           "
    // "           "
    // "   wwwww   "
    // "   wwwww   "
    // "   wwwww   "
    // "   wwwww   "
    // "   wwwww   "
    // "   wwww        "
    // "           "
    // "           "
    // "           ";
    // draw_img(u,v, img);
    // pc.printf("invisible draw\r\n");
    uLCD.filled_rectangle(u, v, u + 10, v+10, 0XFFFFFF);
}

void draw_noninvert(int u, int v) {
    const char* img = 
    "    W      "
    "   WWW     "
    "  WWWWW    "
    " WWWWWWW   "
    "   WWW     "
    "   WWW     "
    "   WWW     "
    " WWWWWWW   "
    "  WWWWW    "
    "   WWW     "
    "    W      ";
    draw_img(u, v, img);
    pc.printf("noninvert drawn\r\n");
}

void draw_theend(int u, int v) {
    const char* img =
    "  RR   RR  "
    "  RR   RR  "
    "  RR   RR  "
    "  RR   RR  "
    "           "
    "           "
    "    RRR    "
    "  R     R  "
    "R         R"
    "           "
    "           ";
    draw_img(u, v, img);
    
}
void draw_viper_body(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
     const char* img = 
    "LWLWLWLWLWL"
    "WLWLWLWLWLW"
    "LWLWLWLWLWL"
    "WLWLWLWLWLW"
    "LWLWLWLWLWL"
    "WLWLWLWLWLW"
    "LWLWLWLWLWL"
    "WLWLWLWLWLW"
    "LWLWLWLWLWL"
    "WLWLWLWLWLW"
    "LWLWLWLWLWL";

    draw_img(u, v, img);
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    
}

void draw_viper_head(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper

    // }
    uLCD.filled_rectangle(u, v, u+10, v+10, 0X9284C2);
    uLCD.circle(u+5, v+3, 1, RED);
    uLCD.circle(u+5, v+7, 1, RED);
}

void draw_viper_tail(int u, int v)
{
     const char* img =
    "WLLLLLLLLLW"
    "WLLLLLLLLLW"
    "WWWWWWWWWWW"
    "WWWWWWWWWWW"
    "WLLLLLLLLLW"
    "WLLLLLLLLLW"
    "WWWWWWWWWWW"
    "WWWWWWWWWWW"
    "WLLLLLLLLLW"
    "WLLLLLLLLLW"
    "WWWWWWWWWWW";
    // TODO: Implement
    //May need to design a viper tail sprite
    //Tile still need to be designed on paper
    draw_img(u, v, img);
}
