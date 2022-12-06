// ============================================
// The Viper class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "viper.h"

void viper_init (Viper * v)
{
    // TODO: Implement
    //1. Set starting coordinates for your viper head and previous
    v->head_x = 5;             //starting coordinates for viper head
    v->head_y = 5;

    v->head_px = 4;            //starting coordinates for head previous
    v->head_py = 5;

    // Initialize invincible to false
    v->invincible = false;

    //2. Initialize all location for your maximum viper body (loop through the viper)
    for (int i = 0; i < 50; i++) {
        v->locations[i].x = v->head_x;
        v->locations[i].y = v->head_y;
    }
    //3. Set starting length of your viper
    v->length = 3;
    //4. Set starting coordinates for the rest of viper body from starting length
    v->locations[0].x = 5;
    v->locations[0].y = 5;

    v->locations[1].x = 4;
    v->locations[1].y = 5;

    v->locations[2].x = 3;
    v->locations[2].y = 5;
    //5. Initialize viper status
    v->score = 0;
    // initialize viper lives
    v->lives = 3;
    v->frozen = false;
}
