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
#define TETR_BEZEL_Y TETR_HUD_HEIGHT+5
#define TETR_BEZEL_WIDTH TETR_BLOCK_SIZE*TETR_NUM_HORIZONTAL
#define TETR_BEZEL_HEIGHT TETR_BLOCK_SIZE*TETR_NUM_VERTICAL

#define TETR_SPAWN_COL TETR_NUM_HORIZONTAL/2-1

#define TETR_SCREEN_WIDTH TETR_BEZEL_X+TETR_BEZEL_WIDTH+5
#define TETR_SCREEN_HEIGHT TETR_BEZEL_Y+TETR_BEZEL_HEIGHT+5

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

// All possible orientations of tetrominos. In 4x4 matrix forms, flattened.
// Defined as short integer, 2 bytes.
#define SH_T_UP 58368 //1110 0100 0000 0000
#define SH_T_LF 35968 //1000 1100 1000 0000
#define SH_T_DW 19968 //0100 1110 0000 0000
#define SH_T_RT 19520 //0100 1100 0100 0000

#define SH_O_UP 52224 //1100 1100 0000 0000
#define SH_O_LF 52224 //1100 1100 0000 0000
#define SH_O_DW 52224 //1100 1100 0000 0000
#define SH_O_RT 52224 //1100 1100 0000 0000

#define SH_I_UP 61440 //1111 0000 0000 0000
#define SH_I_LF 34952 //1000 1000 1000 1000
#define SH_I_DW 61440 //1111 0000 0000 0000
#define SH_I_RT 34952 //1000 1000 1000 1000

#define SH_L_UP 35008 //1000 1000 1100 0000
#define SH_L_LF 11776 //0010 1110 0000 0000
#define SH_L_DW 50240 //1100 0100 0100 0000
#define SH_L_RT 59392 //1110 1000 0000 0000

#define SH_J_UP 17600 //0100 0100 1100 0000
#define SH_J_LF 57856 //1110 0010 0000 0000
#define SH_J_DW 51328 //1100 1000 1000 0000
#define SH_J_RT 36352 //1000 1110 0000 0000

#define SH_S_UP 27648 //0110 1100 0000 0000
#define SH_S_LF 35904 //1000 1100 0100 0000
#define SH_S_DW 27648 //0110 1100 0000 0000
#define SH_S_RT 35904 //1000 1100 0100 0000

#define SH_Z_UP 50688 //1100 0110 0000 0000
#define SH_Z_LF 19584 //0100 1100 1000 0000
#define SH_Z_DW 50688 //1100 0110 0000 0000
#define SH_Z_RT 19584 //0100 1100 1000 0000

typedef struct Tetrominos {
    int row;
    int col;
    SDL_Color *color;
    // This is a string representation of the matrix. Get the total matrix by using rows and cols.
    int *matrix;
    // short matrix;
    int code;
} Tetromino;

int loop(int cmd, Uint32 t);
int setup();

extern SDL_Renderer *tetrRend;

#endif /* game_h */
