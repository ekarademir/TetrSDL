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

SDL_Color COLOR_WHITE = {255, 255, 255, 255};
SDL_Color COLOR_BLACK = {0, 0, 0, 255};
SDL_Color COLOR_BLUE1 = {0, 114, 188, 255};
SDL_Color COLOR_ORANGE1 = {255, 164, 14, 255};
SDL_Color COLOR_YELLOW1 = {255, 215, 3, 255};
SDL_Color COLOR_GREEN1 = {86, 191, 38, 255};
SDL_Color COLOR_LILAC1 = {117, 173, 241, 255};
SDL_Color COLOR_RED1 = {214, 85, 80, 255};

int TETROMINO_O[6] = {1, 1, 1, 1, 0, 0};
int TETROMINO_T[6] = {1, 1, 1, 0, 1, 0};
int TETROMINO_I[6] = {1, 1, 1, 1, 1, 1};
int TETROMINO_L[6] = {1, 0, 1, 0, 1, 1};
int TETROMINO_J[6] = {0, 1, 0, 1, 1, 1};
int TETROMINO_S[6] = {0, 1, 1, 1, 1, 0};
int TETROMINO_Z[6] = {1, 1, 0, 0, 1, 1};

char hudText[30];
void updateHUD();
void drawBezel();

/**
 * Game loop
 * @param cmd Command flag from the main function. Like key press.
 * @param t Time passed since SDL is initialised.
 */
int loop(int cmd, Uint32 t)
{
    if ((t - last) >= speed){last = t;}
    
    updateHUD();
    drawBezel();
    
    if (cmd == GAME_QUIT){feedback = GAME_QUIT;}
    
    return feedback;
}


Tetromino newTetromino(char shape)
{
    Tetromino t;
    t.row = 2;
    t.col = 3;
    t.shape = 'T';
    t.matrix = TETROMINO_T;
    
    return t;
}


void updateHUD()
{
    sprintf(hudText, "%3d                 LEVEL:%3d", score, level);
    fillTextShaded(hudText, 5, 0, TETR_SCREEN_WIDTH-10, TETR_HUD_HEIGHT, COLOR_WHITE, COLOR_BLACK);
}

void drawBezel()
{
    frameRect(TETR_BEZEL_X, TETR_BEZEL_Y, TETR_BEZEL_WIDTH, TETR_BEZEL_HEIGHT, COLOR_WHITE);
}
