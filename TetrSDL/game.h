//
//  game.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef game_h
#define game_h

#include "imports.h"
#include "utils.h"
#include "scene.h"

#define TETR_SCREEN_WIDTH 500
#define TETR_SCREEN_HEIGHT 625

#define TETR_BLOCK_SIZE 20

#define GAME_NOOP 0
#define GAME_QUIT 1
#define GAME_MOVELEFT 2
#define GAME_MOVERIGHT 3
#define GAME_MOVEDOWN 4
#define GAME_ROTATE 5
#define GAME_NEWGAME 6
#define GAME_PAUSE 8

#define GAME_STATE_PLAY 1
#define GAME_STATE_PAUSE 2

int loop(int cmd, Uint32 t);

extern SDL_Renderer *tetrRend;

#endif /* game_h */
