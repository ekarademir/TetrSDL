//
//  tetr.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 24/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef tetr_h
#define tetr_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "scene.h"
#include "game.h"

#define TETR_SCREEN_WIDTH 300
#define TETR_SCREEN_HEIGHT 600

void createWindow();
void createRenderer();

SDL_Window *tetrWin;
SDL_Renderer *tetrRend;

#endif /* tetr_h */
