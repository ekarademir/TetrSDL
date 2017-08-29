//
//  game.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "game.h"

char hudText[40];
void updateHUD();
void drawBezel();
void drawTetromino(Tetromino *t, int x, int y);
void nextTetromino();
void drawScene();

Uint32 last = 0;  // Last save of the time passed.
int speed = 1000; // Speed of block movement in ms.
int score = 999;
int level = 999;
int state = GAME_STATE_PAUSE;
int feedback = GAME_NOOP;
Tetromino activeShape;
Tetromino nextShape;

SDL_Color COLOR_WHITE = {255, 255, 255, 255};
SDL_Color COLOR_VOID = {0, 0, 0, 0};
SDL_Color COLOR_BLACK = {0, 0, 0, 255};
SDL_Color COLOR_BLUE1 = {0, 114, 188, 255};
SDL_Color COLOR_ORANGE1 = {255, 164, 14, 255};
SDL_Color COLOR_YELLOW1 = {255, 215, 3, 255};
SDL_Color COLOR_GREEN1 = {86, 191, 38, 255};
SDL_Color COLOR_LILAC1 = {117, 173, 241, 255};
SDL_Color COLOR_LILAC2 = {200, 114, 200, 255};
SDL_Color COLOR_RED1 = {214, 85, 80, 255};

int TETROMINO_O[6] = {1, 1, 1, 1, 0, 0};
int TETROMINO_T[6] = {1, 1, 1, 0, 1, 0};
int TETROMINO_I[6] = {1, 1, 1, 1, 1, 1};
int TETROMINO_L[6] = {1, 0, 1, 0, 1, 1};
int TETROMINO_J[6] = {0, 1, 0, 1, 1, 1};
int TETROMINO_S[6] = {0, 1, 1, 1, 1, 0};
int TETROMINO_Z[6] = {1, 1, 0, 0, 1, 1};

Tetromino SHAPE_T = {2, 3, &COLOR_ORANGE1, TETROMINO_T};
Tetromino SHAPE_O = {2, 2, &COLOR_BLUE1, TETROMINO_O};
Tetromino SHAPE_I = {4, 1, &COLOR_RED1, TETROMINO_I};
Tetromino SHAPE_L = {3, 2, &COLOR_GREEN1, TETROMINO_L};
Tetromino SHAPE_J = {3, 2, &COLOR_YELLOW1, TETROMINO_J};
Tetromino SHAPE_S = {2, 3, &COLOR_LILAC1, TETROMINO_S};
Tetromino SHAPE_Z = {2, 3, &COLOR_LILAC2, TETROMINO_Z};

int scene[TETR_NUM_VERTICAL][TETR_NUM_HORIZONTAL];

int setup()
{
    srand((unsigned) time(NULL));
    
    scene[2][0] = CHR_T;
    scene[2][1] = CHR_O;
    scene[2][2] = CHR_I;
    scene[2][3] = CHR_L;
    scene[2][4] = CHR_S;
    scene[2][5] = CHR_J;
    scene[2][6] = CHR_Z;
    
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
    drawTetromino(&nextShape, TETR_BEZEL_X - TETR_BLOCK_SIZE * 4, TETR_BEZEL_Y + TETR_BLOCK_SIZE * 4);
    drawScene();
    
    if (cmd == GAME_ROTATE)
    {
        nextTetromino();
    }
    
    if (cmd == GAME_QUIT){feedback = GAME_QUIT;}
    
    return feedback;
}


void drawScene()
{
    SDL_Color *color;
    for (int i = 0; i < TETR_NUM_VERTICAL; i++)
    {
        for (int j = 0; j < TETR_NUM_HORIZONTAL; j++)
        {
            
            switch (scene[i][j]) {
                case CHR_T:
                    color = SHAPE_T.color;
                    break;
                
                case CHR_O:
                    color = SHAPE_O.color;
                    break;
                
                case CHR_I:
                    color = SHAPE_I.color;
                    break;
                
                case CHR_L:
                    color = SHAPE_L.color;
                    break;
                
                case CHR_J:
                    color = SHAPE_J.color;
                    break;
                
                case CHR_S:
                    color = SHAPE_S.color;
                    break;
                
                case CHR_Z:
                    color = SHAPE_Z.color;
                    break;
                
                default:
                    color = &COLOR_VOID;
                    break;
            } //end switch
            
            if (scene[i][j] > 0)
            {
                fillRect(
                         TETR_BEZEL_X + 1 + TETR_BLOCK_SIZE * j,
                         TETR_BEZEL_Y + 1 + TETR_BLOCK_SIZE * i,
                         TETR_BLOCK_SIZE - 2,
                         TETR_BLOCK_SIZE - 2,
                         color);
            }
        } // end for j
    } // end for i
}


void drawTetromino(Tetromino *t, int x, int y)
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
                     x + 1 + TETR_BLOCK_SIZE * currCol,
                     y + 1 + TETR_BLOCK_SIZE * currRow,
                     TETR_BLOCK_SIZE - 2,
                     TETR_BLOCK_SIZE - 2,
                     t->color);
        }
    }
}


void nextTetromino()
{
    int r = rand() % 7 + 1;
    
    Tetromino t;
    
    switch (r) {
        case CHR_I:
            t = SHAPE_I;
            break;
        
        case CHR_O:
            t = SHAPE_O;
            break;
        
        case CHR_L:
            t = SHAPE_L;
            break;
        
        case CHR_J:
            t = SHAPE_J;
            break;
        
        case CHR_S:
            t = SHAPE_S;
            break;
        
        case CHR_Z:
            t = SHAPE_Z;
            break;
            
        default: // CHR_T
            t = SHAPE_T;
            break;
    }

    nextShape = t;
}


void updateHUD()
{
    sprintf(hudText, "%3d                    LEVEL: %3d", score, level);
    fillTextShaded(hudText, 22, -1, TETR_SCREEN_WIDTH-10, TETR_HUD_HEIGHT, &COLOR_WHITE, &COLOR_BLACK);
}

void drawBezel()
{
    frameRect(TETR_BEZEL_X - 1, TETR_BEZEL_Y - 1, TETR_BEZEL_WIDTH + 2, TETR_BEZEL_HEIGHT + 2, &COLOR_WHITE);
}
