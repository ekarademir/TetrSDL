//
//  tetr.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 24/08/2017.
//  Copyright © 2017 See LICENSE.
//

#ifndef tetr_h
#define tetr_h

#include "imports.h"
#include "utils.h"
#include "scene.h"
#include "game.h"

int createWindow();
int createRenderer();
int loadFont();

SDL_Window *tetrWin;
SDL_Renderer *tetrRend;
TTF_Font *tetrFont;

#endif /* tetr_h */
