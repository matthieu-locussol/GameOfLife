#ifndef DEF_MAIN
#define DEF_MAIN

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "settings.h"
#include "cells.h"
#include "buttons.h"
#include "schemas.h"

#define GOL_UNREFERENCED_PARAMETER(p) { (p) = (p); }

#define GOL_WINDOW_WIDTH 644
#define GOL_WINDOW_HEIGHT 694
#define GOL_WINDOW_TITLE "Game of life"

void GOL_Initialisation(void);

void GOL_Screen_Initialisation(
	SDL_Surface** golScreen
	);

void GOL_Background_Initialisation(
	SDL_Surface** golBackground
	);

void GOL_Quit(
	SDL_Surface* golBackground,
	SDL_Surface* golGrid,
	SDL_Surface* golCellVirgin,
	SDL_Surface* golCellAlive,
	SDL_Surface* golCellDead,
	GOL_Cell_Grid* golCellGrid,
	GOL_Button_Group* golButtonGroup,
	GOL_Settings* golSettings
	);

#endif
