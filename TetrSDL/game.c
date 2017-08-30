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
void drawTetromino2(Tetromino *t, int x, int y);
void copyTetromino(Tetromino *source, Tetromino *target);
void destroyTetromino(Tetromino *t);
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

int TETROMINO_O[6] = {1, 1, 1, 1, 0, 0};
int TETROMINO_T[6] = {1, 1, 1, 0, 1, 0};
int TETROMINO_I[6] = {1, 1, 1, 1, 1, 1};
int TETROMINO_L[6] = {1, 0, 1, 0, 1, 1};
int TETROMINO_J[6] = {0, 1, 0, 1, 1, 1};
int TETROMINO_S[6] = {0, 1, 1, 1, 1, 0};
int TETROMINO_Z[6] = {1, 1, 0, 0, 1, 1};
int TETROMINO_VOID[6] = {0, 0, 0, 0, 0, 0};

Tetromino SHAPE_T = {2, 3, &COLOR_ORANGE1, TETROMINO_T, CHR_T, SH_T_UP};
Tetromino SHAPE_O = {2, 2, &COLOR_BLUE1, TETROMINO_O, CHR_O, SH_O_UP};
Tetromino SHAPE_I = {4, 1, &COLOR_RED1, TETROMINO_I, CHR_I, SH_I_UP};
Tetromino SHAPE_L = {3, 2, &COLOR_GREEN1, TETROMINO_L, CHR_L, SH_L_UP};
Tetromino SHAPE_J = {3, 2, &COLOR_YELLOW1, TETROMINO_J, CHR_J, SH_J_UP};
Tetromino SHAPE_S = {2, 3, &COLOR_LILAC1, TETROMINO_S, CHR_S, SH_S_UP};
Tetromino SHAPE_Z = {2, 3, &COLOR_LILAC2, TETROMINO_Z, CHR_Z, SH_Z_UP};

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
    int len = t->col * t->row;
    
    int currCol, currRow;
    
    arenaToScene();
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / t->col;
        currCol = i % t->col;
        
        if (t->matrix[i] == 1)
        {
            scene[activeY + currRow][activeX + currCol] = t->code;
        }
        else
        {
            scene[activeY + currRow][activeX + currCol] = 0;
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
//    drawTetromino(&nextShape, TETR_BEZEL_X - TETR_BLOCK_SIZE * 4, TETR_BEZEL_Y + TETR_BLOCK_SIZE * 4);
    drawTetromino2(&nextShape, TETR_BEZEL_X - TETR_BLOCK_SIZE * 4, TETR_BEZEL_Y + TETR_BLOCK_SIZE * 4);
}


void moveActiveShape(int dx, int dy)
{
    activeX += dx;
    activeY += dy;
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

void drawTetromino2(Tetromino *t, int x, int y)
{
    
    int len = 16;
    
    int collen = 4;
    
    int currRow, currCol;
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / collen;
        currCol = i % collen;
        if ( (t->orientation & POS[i]) != 0)
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
//    int r = rand() % 7 + 1;
    int r = 7;
    
    destroyTetromino(&nextShape);
    
    switch (r) {
        case CHR_I:
            copyTetromino(&nextShape, &SHAPE_I);
            break;
        
        case CHR_O:
            copyTetromino(&nextShape, &SHAPE_O);
            break;
        
        case CHR_L:
            copyTetromino(&nextShape, &SHAPE_L);
            break;
        
        case CHR_J:
            copyTetromino(&nextShape, &SHAPE_J);
            break;
        
        case CHR_S:
            copyTetromino(&nextShape, &SHAPE_S);
            break;
        
        case CHR_Z:
            copyTetromino(&nextShape, &SHAPE_Z);
            break;
            
        default: // CHR_T
            copyTetromino(&nextShape, &SHAPE_T);
            break;
    }
}

void newShape()
{
    nextTetromino();
    copyTetromino(&activeShape, &nextShape);
}


void rotateActiveShape()
{
    printTetromino(&activeShape);
    transposeShape();
    printTetromino(&activeShape);
    flipVShape();
    printTetromino(&activeShape);
}


void transposeShape()
{
    int newCol = activeShape.row;
    int newRow = activeShape.col;
    
    int len = newCol * newRow;
    
    int tRow, tCol, j, t;
    
    for (int i = 0; i < len; i++)
    {
        tCol = i / activeShape.col; // row
        tRow = i % activeShape.col; // col
        
        j = newCol * tRow + tCol;
        
        t = activeShape.matrix[i];
        activeShape.matrix[i] = activeShape.matrix[j];
        activeShape.matrix[j] = t;
    }
    
    activeShape.col = newCol;
    activeShape.row = newRow;
}


void printTetromino(Tetromino *t)
{
    int len = t->row * t->col;
    
    int tCol;
    
    for (int i = 0; i < len; i++)
    {
        tCol = i % t->col; // col
        
        printf("%d ", t->matrix[i]);
        
        if (tCol == t->col - 1 )
        {
            printf("\n");
        }
        
    }
    
    printf("\n");
}


void flipVShape()
{
    if (activeShape.col > 1)
    {
        int len = activeShape.row * activeShape.col;
        
        int tRow, tCol, j, t;
        
        for (int i = 0; i < len; i++)
        {
            tRow = i / activeShape.col;
            tCol = i % activeShape.col;
            
            if (activeShape.col == 2)
            {
                if (tCol == 1){tCol = 0;}
                if (tCol == 0){tCol = 1;}
            }
            else // == 3
            {
                if (tCol == 0){tCol = 2;}
                if (tCol == 2){tCol = 0;}
            }
            
            j = activeShape.col * tRow + tCol;
            
            t = activeShape.matrix[i];
            activeShape.matrix[i] = activeShape.matrix[j];
            activeShape.matrix[j] = t;
            
        }
    }
    
}


void copyTetromino(Tetromino *target, Tetromino *source)
{
    if (target->matrix == NULL)
    {
        target->col = 2;
        target->row = 3;
        target->color = &COLOR_VOID;
        target->matrix = TETROMINO_VOID;
        target->code = CHR_T;
        target->orientation = 0;
    }
    
    target->col = source->col;
    target->row = source->row;
    target->color = source->color;
    target->code = source->code;
    target->orientation = source->orientation;
    
    for (int i = 0; i < 6; i++)
    {
        target->matrix[i] = source->matrix[i];
    }
}


void destroyTetromino(Tetromino *t)
{
    if (t->matrix != NULL)
    {
        for (int i = 0; i < 6; i++)
        {
            t->matrix[i] = 0;
        }
    }
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
