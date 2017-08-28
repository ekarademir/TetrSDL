//
//  game.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef game_h
#define game_h

#include "imports.h"
#include "utils.h"
#include "scene.h"

#define TETR_BLOCK_SIZE 20
#define TETR_NUM_HORIZONTAL 20
#define TETR_NUM_VERTICAL 35
#define TETR_HUD_HEIGHT 25

#define TETR_BEZEL_PADDING 35
#define TETR_BEZEL_X TETR_BLOCK_SIZE*3+TETR_BEZEL_PADDING
#define TETR_BEZEL_Y 23
#define TETR_BEZEL_WIDTH TETR_BLOCK_SIZE*TETR_NUM_HORIZONTAL
#define TETR_BEZEL_HEIGHT TETR_BLOCK_SIZE*TETR_NUM_VERTICAL
#define TETR_BEZEL_CENTER TETR_BLOCK_SIZE*(TETR_NUM_HORIZONTAL/2+2) + TETR_BEZEL_PADDING

#define TETR_SCREEN_WIDTH TETR_BEZEL_X+TETR_BEZEL_WIDTH+5
#define TETR_SCREEN_HEIGHT TETR_HUD_HEIGHT+TETR_BEZEL_HEIGHT

#define GAME_NOOP 0
#define GAME_QUIT 1
#define GAME_MOVELEFT 2
#define GAME_MOVERIGHT 3
#define GAME_MOVEDOWN 4
#define GAME_ROTATE 5
#define GAME_NEWGAME 6
#define GAME_PAUSE 8

#define GAME_STATE_PLAY 1
#define GAME_STATE_PAUSE 2

#define CHR_T 7
#define CHR_I 1
#define CHR_S 2
#define CHR_Z 3
#define CHR_J 4
#define CHR_L 5
#define CHR_O 6

typedef struct Tetrominos {
    int row;
    int col;
    SDL_Color *color;
    // This is a string representation of the matrix. Get the total matrix by using rows and cols.
    int *matrix;
} Tetromino;

int loop(int cmd, Uint32 t);
int setup();

extern SDL_Renderer *tetrRend;

#endif /* game_h */
