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
void printTetromino(Tetromino *t);

void drawScene();
void arenaToScene();
void drawNextShape();
void blendToScene(Tetromino *t);
void moveActiveShape(int dx, int dy);
void transposeShape();
void flipVShape();
void rotateActiveShape();
void newShape();


Uint32 last = 0;  // Last save of the time passed.
int speed = 1000; // Speed of block movement in ms.
int score = 999;
int level = 999;
int state = GAME_STATE_PAUSE;
int feedback = GAME_NOOP;
Tetromino activeShape;
Tetromino nextShape;
int activeX;
int activeY;

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

unsigned short POS[16] = {
    _BIT1,  _BIT2,  _BIT3,  _BIT4,  _BIT5,  _BIT6, _BIT7, _BIT8, _BIT9, _BIT10,
    _BIT11, _BIT12, _BIT13, _BIT14, _BIT15, _BIT16
};

int ORS[7][4] = {
    {SH_I_UP, SH_I_LF, SH_I_DW, SH_I_RT},
    {SH_S_UP, SH_S_LF, SH_S_DW, SH_S_RT},
    {SH_Z_UP, SH_Z_LF, SH_Z_DW, SH_Z_RT},
    {SH_J_UP, SH_J_LF, SH_J_DW, SH_J_RT},
    {SH_L_UP, SH_L_LF, SH_L_DW, SH_L_RT},
    {SH_O_UP, SH_O_LF, SH_O_DW, SH_O_RT},
    {SH_T_UP, SH_T_LF, SH_T_DW, SH_T_RT}
};

Tetromino SHAPE_T = {&COLOR_ORANGE1, CHR_T, SH_T_UP, OR_UP};
Tetromino SHAPE_O = {&COLOR_BLUE1,   CHR_O, SH_O_UP, OR_UP};
Tetromino SHAPE_I = {&COLOR_RED1,    CHR_I, SH_I_UP, OR_UP};
Tetromino SHAPE_L = {&COLOR_GREEN1,  CHR_L, SH_L_UP, OR_UP};
Tetromino SHAPE_J = {&COLOR_YELLOW1, CHR_J, SH_J_UP, OR_UP};
Tetromino SHAPE_S = {&COLOR_LILAC1,  CHR_S, SH_S_UP, OR_UP};
Tetromino SHAPE_Z = {&COLOR_LILAC2,  CHR_Z, SH_Z_UP, OR_UP};

int scene[TETR_NUM_VERTICAL][TETR_NUM_HORIZONTAL];
int arena[TETR_NUM_VERTICAL][TETR_NUM_HORIZONTAL];

int setup()
{
    srand((unsigned) time(NULL));
    
    activeX = TETR_SPAWN_COL;
    
    nextTetromino();
    newShape();
    
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
    drawNextShape();
    blendToScene(&activeShape);
    drawScene();
    
    if (cmd == GAME_ROTATE)
    {
        rotateActiveShape();
    }
    
    if (cmd == GAME_MOVELEFT)
    {
        moveActiveShape(-1, 0);
    }
    
    if (cmd == GAME_MOVERIGHT)
    {
        moveActiveShape(1, 0);
    }
    
    if (cmd == GAME_MOVEDOWN)
    {
        moveActiveShape(0, 1);
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


void blendToScene(Tetromino *t)
{
    int len = 16;
    
    int collen = 4;
    
    int currCol, currRow;
    
    arenaToScene();
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / collen;
        currCol = i % collen;
        
        if ( (t->repr & POS[i]) != 0 )
        {
            scene[activeY + currRow][activeX + currCol] = t->code;
        }
    }
}


void arenaToScene()
{
    for (int i = 0; i < TETR_NUM_VERTICAL; i++)
    {
        for (int j = 0; j < TETR_NUM_HORIZONTAL; j++)
        {
            scene[i][j] = arena[i][j];
        }
    }
}

void drawNextShape()
{
    drawTetromino(&nextShape, TETR_BEZEL_X - TETR_BLOCK_SIZE * 4, TETR_BEZEL_Y + TETR_BLOCK_SIZE * 4);
}


void moveActiveShape(int dx, int dy)
{
    activeX += dx;
    activeY += dy;
}


void drawTetromino(Tetromino *t, int x, int y)
{
    
    int len = 16;
    
    int collen = 4;
    
    int currRow, currCol;
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / collen;
        currCol = i % collen;
        if ( (t->repr & POS[i]) != 0)
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
//    int r = 6;
    
    switch (r) {
        case CHR_I:
            nextShape = SHAPE_I;
            break;
        
        case CHR_O:
            nextShape = SHAPE_O;
            break;
        
        case CHR_L:
            nextShape = SHAPE_L;
            break;
        
        case CHR_J:
            nextShape = SHAPE_J;
            break;
        
        case CHR_S:
            nextShape = SHAPE_S;
            break;
        
        case CHR_Z:
            nextShape = SHAPE_Z;
            break;
            
        default: // CHR_T
            nextShape = SHAPE_T;
            break;
    }
}

void newShape()
{
    nextTetromino();
    activeShape = nextShape;
}


void rotateActiveShape()
{
    activeShape.direction = (activeShape.direction + 1) % 4;
    activeShape.repr = ORS[activeShape.code - 1][activeShape.direction];
}


void printTetromino(Tetromino *t)
{
    int len = 16;
    
    int collen = 4;
    
    int tCol;
    
    for (int i = 0; i < len; i++)
    {
        tCol = i % collen;
        
        printf("%d ",  ((t->repr & POS[i]) != 0) );
        
        if (tCol == collen -1 )
        {
            printf("\n");
        }
        
    }
    
    printf("\n");
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
