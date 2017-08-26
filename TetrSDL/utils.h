//
//  utils.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <SDL2/SDL.h>

#define LOG_CRT 50
#define LOG_ERR 40
#define LOG_WRN 30
#define LOG_INF 20
#define LOG_DBG 10


void logger(int lvl, char *msg);
void cleanUp();

extern SDL_Window *tetrWin;
extern SDL_Renderer *tetrRend;

#endif /* utils_h */
