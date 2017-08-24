//
//  tetr.h
//  TetrSDL
//
//  Created by Ertugrul Karademir on 24/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//

#ifndef tetr_h
#define tetr_h

#define TETR_SCREEN_WIDTH 300
#define TETR_SCREEN_HEIGHT 600

#define LOG_CRT 50
#define LOG_ERR 40
#define LOG_WRN 30
#define LOG_INF 20
#define LOG_DBG 10


SDL_Window *tetrWin;
SDL_Renderer *tetrRend;

void cleanUp();
void logger();
void createWindow();
void createRenderer();

#endif /* tetr_h */
