//
//  game.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "game.h"

char hudText[30];
void updateHUD();
void drawBezel();
void drawTetromino(Tetromino *t);
void nextTetromino();


Uint32 last = 0;  // Last save of the time passed.
int speed = 1000; // Speed of block movement in ms.
int score = 999;
int level = 999;
int state = GAME_STATE_PAUSE;
int feedback = GAME_NOOP;
Tetromino *activeShape;
Tetromino *nextShape;

SDL_Color COLOR_WHITE = {255, 255, 255, 255};
SDL_Color COLOR_BLACK = {0, 0, 0, 255};
SDL_Color COLOR_BLUE1 = {0, 114, 188, 255};
SDL_Color COLOR_ORANGE1 = {255, 164, 14, 255};
SDL_Color COLOR_YELLOW1 = {255, 215, 3, 255};
SDL_Color COLOR_GREEN1 = {86, 191, 38, 255};
SDL_Color COLOR_LILAC1 = {117, 173, 241, 255};
SDL_Color COLOR_LILAC2 = {107, 173, 221, 255};
SDL_Color COLOR_RED1 = {214, 85, 80, 255};

int TETROMINO_O[6] = {1, 1, 1, 1, 0, 0};
int TETROMINO_T[6] = {1, 1, 1, 0, 1, 0};
int TETROMINO_I[6] = {1, 1, 1, 1, 1, 1};
int TETROMINO_L[6] = {1, 0, 1, 0, 1, 1};
int TETROMINO_J[6] = {0, 1, 0, 1, 1, 1};
int TETROMINO_S[6] = {0, 1, 1, 1, 1, 0};
int TETROMINO_Z[6] = {1, 1, 0, 0, 1, 1};


Tetromino SHAPE_T = {'T', 2, 3, &COLOR_ORANGE1, TETROMINO_T, 0, 0};
Tetromino SHAPE_O = {'O', 2, 2, &COLOR_BLUE1, TETROMINO_O, 0, 0};
Tetromino SHAPE_I = {'I', 4, 1, &COLOR_RED1, TETROMINO_I, 0, 0};
Tetromino SHAPE_L = {'L', 3, 2, &COLOR_GREEN1, TETROMINO_L, 0, 0};
Tetromino SHAPE_J = {'J', 3, 2, &COLOR_YELLOW1, TETROMINO_J, 0, 0};
Tetromino SHAPE_S = {'S', 2, 3, &COLOR_LILAC1, TETROMINO_S, 0, 0};
Tetromino SHAPE_Z = {'Z', 2, 3, &COLOR_LILAC2, TETROMINO_Z, 0, 0};



int setup()
{
    srand((unsigned) time(NULL));
    
     nextTetromino();
    
    return 0;
}


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
    drawTetromino(nextShape);
    
    if (cmd == GAME_ROTATE)
    {
        nextTetromino();
    }
    
    if (cmd == GAME_QUIT){feedback = GAME_QUIT;}
    
    return feedback;
}


void drawTetromino(Tetromino *t)
{
    int len = t->col * t->row;
    
    int currCol, currRow;
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / t->col;
        currCol = i % t->col;

        if (t->matrix[i] == 1)
        {
            fillRect(
                     t->xPos + 1 + TETR_BLOCK_SIZE * currCol,
                     t->yPos + 1 + TETR_BLOCK_SIZE * currRow,
                     TETR_BLOCK_SIZE-2,
                     TETR_BLOCK_SIZE -2,
                     t->color);
        }
    }
}


void nextTetromino()
{
    int r = rand() % 7;
    
    Tetromino *t;
    
    switch (r) {
        case 0:
            t = &SHAPE_I;
            break;
        
        case 1:
            t = &SHAPE_O;
            break;
        
        case 2:
            t = &SHAPE_L;
            break;
        
        case 3:
            t = &SHAPE_J;
            break;
        
        case 4:
            t = &SHAPE_S;
            break;
        
        case 5:
            t = &SHAPE_Z;
            break;
            
        default:
            t = &SHAPE_T;
            break;
    }
    
    
    t->xPos = TETR_BEZEL_X - TETR_BLOCK_SIZE * 4;
    t->yPos = TETR_BEZEL_Y + TETR_BLOCK_SIZE * 4;

    nextShape = t;
}


void updateHUD()
{
    sprintf(hudText, "%3d                 LEVEL:%3d", score, level);
    fillTextShaded(hudText, 5, 0, TETR_SCREEN_WIDTH-10, TETR_HUD_HEIGHT, &COLOR_WHITE, &COLOR_BLACK);
}

void drawBezel()
{
    frameRect(TETR_BEZEL_X, TETR_BEZEL_Y, TETR_BEZEL_WIDTH, TETR_BEZEL_HEIGHT, &COLOR_WHITE);
}
