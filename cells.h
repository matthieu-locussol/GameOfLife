#ifndef DEF_CELLS
#define DEF_CELLS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "SDL.h"

#include "settings.h"

#define GOL_CELL_MAX_SIZE 80
#define GOL_CELL_MIN_SIZE 5

typedef enum GOL_State GOL_State;
typedef struct GOL_Cell GOL_Cell;
typedef struct GOL_Cell_Grid GOL_Cell_Grid;

enum GOL_State { VIRGIN, DEAD, ALIVE };

struct GOL_Cell
{

	GOL_State cState;

	/*
	 * Cell's position (cells)
	 */

	int cX;
	int cY;

	/*
	 * Cell's neighboors
	 */

	int cNeighboors;

	/*
	 * Cell's position (pixels)
	 */

	SDL_Rect cPosition;

};

struct GOL_Cell_Grid
{

	/*
	 * Cells grid (only states)
	 */

	GOL_Cell** cgCellGrid;

};

int GOL_Cell_Valid_Coordinates(
	int cX,
	int cY,
	GOL_Settings golSettings
	);

int GOL_Cell_X_CoordinatesFromReal(
	int cX,
	GOL_Settings* golSettings
	);

int GOL_Cell_Y_CoordinatesFromReal(
	int cY,
	GOL_Settings* golSettings
	);

void GOL_Cell_Initialisation(
	GOL_Cell* golCell,
	GOL_Settings* golSettings
	);

void GOL_Cells_Initialisation(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Settings* golSettings
	);

int GOL_Cell_Neighboors_Calculation(
	GOL_Cell golCell,
	GOL_Cell_Grid golCellGrid,
	GOL_Settings golSettings
	);

void GOL_Cell_State_Calculation(
	GOL_Cell* golCell,
	GOL_Cell* golNewCell
	);

void GOL_Cell_Display(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Cell* golCell
	);

void GOL_Cell_SetAlive(
	GOL_Cell* golCell
	);

void GOL_Cell_SetVirgin(
	GOL_Cell* golCell
	);

void GOL_Cell_Grid_Initialisation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_Neighboors_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_State_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Cell_Grid* golNewCellGrid,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_NextGen_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_Assignment(
	GOL_Cell_Grid* golCellGridX,
	GOL_Cell_Grid* golCellGridY,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_Display(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void GOL_Cell_Grid_MouseClickHandle(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings,
	int motionX,
	int motionY,
	Uint8 button
	);

int GOL_Cell_Grid_MouseInGame(
	int motionX,
	int motionY
	);

void GOL_Cell_Grid_Free(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

#endif
