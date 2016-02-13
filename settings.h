#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#define GOL_SETTINGS_FPS 50

#define GOL_SETTINGS_GAME_DIMENSION 640

#define GOL_SETTINGS_GAME_OFFSET_X 2
#define GOL_SETTINGS_GAME_OFFSET_Y 2

#define GOL_SETTINGS_DEFAULT_CELL_SIZE 32

typedef struct GOL_Settings GOL_Settings;

struct GOL_Settings
{

	/*
	 * Boolean :: (1: program continues, 0: program stops)
	 */

	int sRun;

	/*
	 * Tools :: (0: pencil, 1: brush)
	 */

	int sTool;

	/*
	 * Time elapsed since last loop
	 */

	int sTimeElapsed;

	/*
	 * Previous value of sTimeElapsed
	 */

	int sPreviousTimeElapsed;

	/*
	 * Size of a single cell (in pixels) : sCellsSize * sCellsSize
	 */

	int sCellsSize;

	/*
	 * Cells number on a single line (cells number : sCellsPerLine * sCellsPerLine)
	 */

	int sCellsPerLine;

	/*
	* Boolean :: (1: calculate next generation at each frame, 0: do nothing)
	*/

	int sGenerationsAuto;

	/*
	* Boolean :: (0: no grid display, 1: displays grid)
	*/

	int sGrid;

	/*
	 * Path to the current grid file
	 */

	char sGridPath[28];

};

void GOL_Settings_Initialisation(
	GOL_Settings* golSettings
	);

void GOL_Settings_Grid_Initialisation(
	SDL_Surface** golGrid,
	GOL_Settings* golSettings
	);

void GOL_Settings_Grid_Display(
	SDL_Surface** golGrid,
	SDL_Surface** golScreen
	);

void GOL_Settings_Size_Minus(
	GOL_Settings* golSettings
	);

void GOL_Settings_Size_Plus(
	GOL_Settings* golSettings
	);

#endif DEF_SETTINGS
