//
//  game.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "game.h"


int x = 0;
int y = 0;
Uint32 last = 0;

int speed = 1000; // Speed of block movement in ms.

int loop(int cmd, Uint32 t)
{
    if ((t - last) >= speed)
    {
        y += 10;
        last = t;
    }
    
    
    if (cmd == GAME_MOVEDOWN)
    {
        y += 20;
    }
    if (cmd == GAME_MOVELEFT)
    {
        x -= 20;
    }
    if (cmd == GAME_MOVERIGHT)
    {
        x += 20;
    }
    if (cmd == GAME_ROTATE)
    {
        y -= 20;
    }
    
    SDL_Color clr = {.r=255, .g=0, .b=0, .a=255};
    
    fillRect(x, y, 100, 100, &clr);
    SDL_RenderPresent(tetrRend);
//    SDL_Delay(1000);
    return 0;
}
