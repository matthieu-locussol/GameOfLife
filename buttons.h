#ifndef DEF_BUTTONS
#define DEF_BUTTONS

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "settings.h"
#include "cells.h"

#define GOL_BUTTONS_NUMBER 9

#define GOL_BUTTONS_PIPE_OFFSET 8

#define GOL_BUTTONS_OFFSET_Y 650
#define GOL_BUTTONS_OFFSET_X 8
#define GOL_BUTTONS_DISTANCE 6

#define GOL_BUTTONS_SIZE 36

#define GOL_BUTTONS_ICON_PATH_LENGTH 33

typedef enum GOL_Button_ID GOL_Button_ID;
typedef struct GOL_Button GOL_Button;
typedef struct GOL_Button_Group GOL_Button_Group;

enum GOL_Button_ID { B_RESET, B_BACKUP, B_PLAY, B_NEXT, B_ZOOMIN, B_ZOOMOUT, B_GRID, B_PENCIL, B_BRUSH };

struct GOL_Button
{

	/*
	 * Button's ID
	 */

	GOL_Button_ID bId;

	/*
	 * Button's hover state
	 */

	int bHoverState;

	/*
	 * Button's focus state
	 */

	int bFocusState;

	/*
	 * Button's icons (default, hovered, focused)
	 */

	SDL_Surface* bIcon[3];

	/*
	 * Button's position (pixels)
	 */

	SDL_Rect bPosition;

};

struct GOL_Button_Group
{

	GOL_Button* bgButtonGroup;

};

int GOL_Button_Valid_Coordinates(
	int cX,
	int cY,
	GOL_Button golButton
	);

void GOL_Button_Initialisation(
	GOL_Button* golButton,
	int pipeOffset
	);

int GOL_Button_MouseHover(
	GOL_Button golButton,
	int motionX,
	int motionY
	);

void GOL_Button_MouseClick(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	SDL_Surface** golGrid,
	GOL_Button_Group* golButtonGroup,
	GOL_Button* golButton,
	GOL_Cell_Grid* golCellGrid,
	GOL_Cell_Grid* golCellGridBackup,
	GOL_Settings* golSettings
	);

void GOL_Button_Group_Initialisation(
	GOL_Button_Group* golButtonGroup
	);

void GOL_Button_Group_Display(
	SDL_Surface** golScreen,
	GOL_Button_Group* golButtonGroup
	);

void GOL_Button_Group_MouseMotionHandle(
	GOL_Button_Group* golButtonGroup,
	int motionX,
	int motionY
	);

void GOL_Button_Group_MouseClickHandle(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	SDL_Surface** golGrid,
	GOL_Button_Group* golButtonGroup,
	GOL_Cell_Grid* golCellGrid,
	GOL_Cell_Grid* golCellGridBackup,
	GOL_Settings* golSettings,
	int motionX,
	int motionY,
	Uint8 button
	);

void GOL_Button_Group_Free(
	GOL_Button_Group* golButtonGroup
	);

#endif
