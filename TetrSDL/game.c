//
//  game.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "game.h"


Uint32 last = 0;  // Last save of the time passed.
int speed = 1000; // Speed of block movement in ms.
int score = 999;
int level = 999;
int state = GAME_STATE_PAUSE;
int feedback = GAME_NOOP;

SDL_Color COLOR_WHITE = {255, 255, 255, 0};
SDL_Color COLOR_BLACK = {255, 255, 255, 0};
SDL_Color COLOR_BLUE1 = {0, 114, 188, 0};
SDL_Color COLOR_ORANGE1 = {255, 164, 14, 0};
SDL_Color COLOR_YELLOW1 = {255, 215, 3, 0};
SDL_Color COLOR_GREEN1 = {86, 191, 38, 0};
SDL_Color COLOR_LILAC1 = {117, 173, 241, 0};
SDL_Color COLOR_RED1 = {214, 85, 80, 0};

char hudText[30];
void updateHUD();

/**
 * Game loop
 * @param cmd Command flag from the main function. Like key press.
 * @param t Time passed since SDL is initialised.
 */
int loop(int cmd, Uint32 t)
{
    if ((t - last) >= speed){last = t;}
    
    updateHUD();
    
    
    if (cmd == GAME_QUIT){feedback = GAME_QUIT;}
    
    return feedback;
}


void updateHUD()
{
    sprintf(hudText, "%3d                 LEVEL:%3d", score, level);
    
    fillText(hudText, 5, 0, TETR_SCREEN_WIDTH-10, 20, COLOR_BLUE1);
}
