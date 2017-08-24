//
//  main.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 23/08/2017.
//  Copyright © 2017 Ertugrul Karademir. See LICENCE for licence info.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include "tetr.h"

int main(int argc, const char * argv[])
{
  // Initialise video and audio subsystems
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    logger(LOG_ERR, "SDL Init Error: %s");
  }
  
  createWindow();
  createRenderer();
  
  cleanUp();
  exit(EXIT_SUCCESS);
}


/**
 * Cleans up the instances.
 */
void cleanUp()
{
  if (tetrWin != NULL)
  {
    SDL_DestroyWindow(tetrWin);
    logger(LOG_DBG, "Destroyed window instance.");
  }
  
  if (tetrRend != NULL)
  {
    SDL_DestroyRenderer(tetrRend);
    logger(LOG_DBG, "Destroyed renderer instance.");
  }
  
  SDL_Quit();
}


/**
 * Wraps SDL Log Handling Subsystem
 *
 * @param lvl Level of the message
 * @param msg Message to log.
 */
void logger(int lvl, char *msg)
{
  if (lvl == LOG_ERR)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
  }
  else if (lvl == LOG_CRT)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
  }
  else if (lvl == LOG_DBG)
  {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
  }
  else if (lvl == LOG_WRN)
  {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
  }
  else if (lvl == LOG_INF)
  {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, "");
  }
  else
  {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, "");
  }
}


/**
 * Wraps SDL_CreateWindow
 */
void createWindow()
{
  tetrWin = SDL_CreateWindow("TETR",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   TETR_SCREEN_WIDTH, TETR_SCREEN_HEIGHT,
                                   SDL_WINDOW_OPENGL);
  
  if (tetrWin == NULL)
  {
    logger(LOG_ERR, "Error creating window: %s");
    cleanUp();
  }
  else
  {
    logger(LOG_DBG, "Created window instance.");
  }

}


/**
 * Wraps SDL_CreateRenderer
 */
void createRenderer()
{
  tetrRend = SDL_CreateRenderer(tetrWin, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
  
  if (tetrRend == NULL)
  {
    logger(LOG_ERR, "Error creating renderer: %s");
    cleanUp();
  }
  else
  {
    logger(LOG_DBG, "Created renderer instance.");
  }
}
