//
//  scene.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#include "scene.h"


void clearScene()
{
    SDL_SetRenderDrawColor(tetrRend, 0, 0, 0, 0);
    SDL_RenderClear(tetrRend);
}


void fillRect (int x, int y, int w, int h, SDL_Color *color)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(tetrRend, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(tetrRend, &rect);
}


void fillText (char *msg, int x, int y, int w, int h, SDL_Color *color)
{
    SDL_Surface *text_surface = TTF_RenderText_Blended(tetrFont, msg, *color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(tetrRend, text_surface);
    SDL_Rect rect = {x, y, w, h};
    SDL_FreeSurface(text_surface);
    SDL_RenderCopy(tetrRend, text, NULL, &rect);
    SDL_DestroyTexture(text);
    text = NULL;
}


void fillTextShaded (char *msg, int x, int y, int w, int h, SDL_Color *color, SDL_Color *bgcolor)
{
    SDL_Surface *text_surface = TTF_RenderUTF8_Shaded(tetrFont, msg, *color, *bgcolor);
    SDL_Texture *text = SDL_CreateTextureFromSurface(tetrRend, text_surface);
    SDL_Rect rect = {x, y, w, h};
    SDL_FreeSurface(text_surface);
    SDL_RenderCopy(tetrRend, text, NULL, &rect);
    SDL_DestroyTexture(text);
    text = NULL;
}


void frameRect (int x, int y, int w, int h, SDL_Color *color)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(tetrRend, color->r, color->g, color->b, color->a);
    SDL_RenderDrawRect(tetrRend, &rect);
}
