//
//  scene.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "scene.h"

void fillRect (int x, int y, int w, int h, SDL_Color *color)
{
    if (color != NULL)
    {
        SDL_Rect rect = {x, y, w, h};
        SDL_SetRenderDrawColor(tetrRend, color->r, color->g, color->b, color->a);
        SDL_RenderFillRect(tetrRend, &rect);
    }
}

void clearScene()
{
    SDL_SetRenderDrawColor(tetrRend, 0, 0, 0, 0);
    SDL_RenderClear(tetrRend);
}
