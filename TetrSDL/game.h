//
//  game.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "scene.h"


#define GAME_QUIT 0
#define GAME_MOVELEFT 1
#define GAME_MOVERIGHT 2
#define GAME_MOVEDOWN 3
#define GAME_ROTATE 4
#define GAME_NEWGAME 5
#define GAME_NOOP 6

int loop(int cmd, Uint32 t);

extern SDL_Renderer *tetrRend;

#endif /* game_h */
