//
//  scene.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef scene_h
#define scene_h

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "utils.h"

void clearScene();
void fillRect (int x, int y, int w, int h, SDL_Color *color);

extern SDL_Renderer *tetrRend;

#endif /* scene_h */
