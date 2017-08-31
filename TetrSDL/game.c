//
//  game.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "game.h"

char hudText[40];


void gameOver();
void updateHUD();
void drawBezel();

void drawTetromino(Tetromino *t, int x, int y);
Tetromino nextTetromino();
void printTetromino(Tetromino *t);

void drawScene();
void arenaToScene();
void seal();
void drawNextShape();
void blendToScene(Tetromino *t);
void blendToArena(Tetromino *t);
Tetromino rotateShape(Tetromino t);

int canMove(int dx, int dy, Tetromino t);
void moveActiveShape(int dx, int dy);
void rotateActiveShape();
void freeFall();
void removeFullLines();
void shiftEmptyLines();
void increaseScore(int amount);

void newShape();
void spawnNew();


Uint32 last = 0;  // Last save of the time passed.
int speed = 1000; // Speed of block movement in ms.
int startSpeed = 1000;
int score = 0;
int level = 1;
int state = GAME_STATE_PLAY;
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

int scene[SCENE_HEIGHT][SCENE_WIDTH];
int arena[SCENE_HEIGHT][SCENE_WIDTH];
int emptyLine[SCENE_WIDTH];

int setup()
{
    srand((unsigned) time(NULL));
    
    state = GAME_STATE_PLAY;
    
    activeX = TETR_SPAWN_COL;
    activeY = TETR_SPAWN_ROW;
    
//    for (int l = 1; l < SCENE_WIDTH-3; l++)
//    {
//        arena[31][l] = 2;
//    }
    
    seal();
    
    nextShape = nextTetromino();
    activeShape = nextTetromino();
    
    return 0;
}


/**
 * Game loop
 * @param cmd Command flag from the main function. Like key press.
 * @param t Time passed since SDL is initialised.
 */
int loop(int cmd, Uint32 t)
{
    if(state == GAME_STATE_PLAY)
    {
        updateHUD();
        drawBezel();
        drawNextShape();
        blendToScene(&activeShape);
        drawScene();
        
        if ((t - last) >= speed)
        {
            last = t;
            freeFall();
        }
        
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
            increaseScore(1);
        }
        
        if (cmd == GAME_MOVEDOWN)
        {
//            state = GAME_STATE_OVER;
            moveActiveShape(0, 1);
        }
    }
    else if(state == GAME_STATE_OVER)
    {
        updateHUD();
        drawBezel();
        drawNextShape();
        drawScene();
        fillText("GAME OVER", TETR_BEZEL_PADDING+150, 300, 0, 0, &COLOR_WHITE);
        if (cmd == GAME_NEWGAME)
        {
            logger(LOG_DBG, "Starting new game %s");
            setup();
        }
    }
    
    if (cmd == GAME_QUIT){feedback = GAME_QUIT;}
    
    return feedback;
}

void removeFullLines()
{
    // H and V should be interchanged but fuck Xcode and its lack of versatile cursors
    int vstart = 1, vend = TETR_NUM_HORIZONTAL+1;
    int hstart = 0, hend = TETR_NUM_VERTICAL;
    
    int fullflag;
    
    for (int i = hstart; i < hend; i++)
    {
        fullflag = 0;
        
        for (int j = vstart; j < vend; j++)
        {
            if (arena[i][j] > 0)
            {
                fullflag++;
            }
            
            if (fullflag == TETR_NUM_HORIZONTAL)
            {
                for (int l = vstart; l < vend; l++)
                {
                    arena[i][l] = 0;
                }
                
                increaseScore(1);
            }
        }
    }
}

void increaseScore(int amount)
{
    score += amount;
    level = (score - (score % 10)) / 10 + 1;
    speed = startSpeed - 50 * level;
}


void shiftEmptyLines()
{
    int hstart = 1, hend = TETR_NUM_HORIZONTAL+1;
    int vstart = 0, vend = TETR_NUM_VERTICAL;
    
    int emptystart = vend - 1, emptycount = 0, emptyflag = 0;
    
    for (int i = vend-1; i >= vstart; i--)
    {
        if (emptycount == 0)
        {
            emptystart = i;
        }
        
        emptyflag = 0;
        for (int j = hstart; j < hend; j++)
        {
            if (arena[i][j] == 0)
            {
                emptyflag++;
            }
        }
        
        if (emptyflag == TETR_NUM_HORIZONTAL)
        {
            emptycount++;
        }
        else
        {
            
            if (emptycount != 0)
            {
                // SHIFT everything above
                for (char k = emptystart; k >= vstart; k--)
                {
                    for (char l = hstart; l < hend; l++)
                    {
                        arena[k][l] = arena[k - emptycount][l];
                    }
                }
                
                // Fill top rows with zero
                for (char k = 0; k < emptycount; k++)
                {
                    for (char l = hstart; l < hend; l++)
                    {
                        arena[k][l] = 0;
                    }
                }
                
                i = vend-1;
                emptycount = 0;
            }
            
        }
    }
}


void seal()
{
    for(int i = 0; i < SCENE_HEIGHT; i++)
    {
        scene[i][0] = 9;
        arena[i][0] = 9;
        
        scene[i][SCENE_WIDTH - 1] = 9;
        arena[i][SCENE_WIDTH - 1] = 9;
    }
    
    for(int i = 0; i < SCENE_WIDTH; i++)
    {
        scene[SCENE_HEIGHT - 1][i] = 9;
        arena[SCENE_HEIGHT - 1][i] = 9;
    }
    
    emptyLine[0] = 9;
    emptyLine[SCENE_WIDTH-1] = 9;
}


void freeFall()
{
    // Test all possible moves if active shape drops one block.
    
    if ( canMove(activeX, activeY + 1, activeShape) )
    {
        activeY++;
    }
    else
    {
        blendToArena(&activeShape);
        spawnNew();
    }
}

void spawnNew()
{
    if (canMove(TETR_SPAWN_COL, 0, nextShape) )
    {
        activeShape = nextShape;
        nextShape = nextTetromino();
        activeY = TETR_SPAWN_ROW;
        activeX = TETR_SPAWN_COL;
    }
    else
    {
        gameOver();
    }
}

void gameOver()
{
    state = GAME_STATE_OVER;
    blendToArena(&nextShape);
}


void drawScene()
{
    SDL_Color *color;
    for (int i = 0; i < SCENE_HEIGHT - 1; i++)
    {
        for (int j = 1; j < SCENE_WIDTH - 1; j++)
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
                         TETR_BEZEL_X + 1 + TETR_BLOCK_SIZE * (j-1),
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


void blendToArena(Tetromino *t)
{
    int len = 16;
    
    int collen = 4;
    
    int currCol, currRow;
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / collen;
        currCol = i % collen;
        
        if ( (t->repr & POS[i]) != 0 )
        {
            arena[activeY + currRow][activeX + currCol] = t->code;
        }
    }
    
    removeFullLines();
    shiftEmptyLines();
}


int canMove(int dx, int dy, Tetromino t)
{
    int len = 16;
    
    int collen = 4;
    
    int currCol, currRow;
    
    arenaToScene();
    
    for (int i = 0; i < len; i++)
    {
        currRow = i / collen;
        currCol = i % collen;
        
        if ( (t.repr & POS[i]) != 0 )
        {
            if (arena[currRow + dy][currCol + dx] > 0)
            {
                return 0;
            }
        }
    }
    
    return 1;
}


void arenaToScene()
{
    for (int i = 0; i < SCENE_HEIGHT; i++)
    {
        for (int j = 0; j < SCENE_WIDTH; j++)
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
    if (canMove(activeX + dx, activeY + dy, activeShape))
    {
        activeX += dx;
        activeY += dy;
    }
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


Tetromino nextTetromino()
{
    Tetromino t;
    int r = rand() % 7 + 1;
//    int r = 6;
    
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
    
    return t;
}

void newShape()
{
    activeShape = nextShape;
    nextShape = nextTetromino();
}

void rotateActiveShape()
{
    Tetromino rotated = rotateShape(activeShape);
    if ( canMove(activeX, activeY, rotated) )
    {
        activeShape = rotated;
    }
}

Tetromino rotateShape(Tetromino t)
{
    t.direction = (t.direction + 1) % 4;
    t.repr = ORS[t.code - 1][t.direction];
    
    return t;
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
