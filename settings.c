#include "settings.h"

void GOL_Settings_Initialisation(
	GOL_Settings* golSettings
	) {

	golSettings->sRun = 1;
	golSettings->sTool = 0;
	golSettings->sTimeElapsed = 0;
	golSettings->sPreviousTimeElapsed = 0;
	golSettings->sCellsSize = GOL_SETTINGS_DEFAULT_CELL_SIZE;
	golSettings->sCellsPerLine = GOL_SETTINGS_GAME_DIMENSION / GOL_SETTINGS_DEFAULT_CELL_SIZE;
	golSettings->sGenerationsAuto = 0;
	golSettings->sGrid = 1;

}

void GOL_Settings_Grid_Initialisation(
	SDL_Surface** golGrid,
	GOL_Settings* golSettings
	) {

	sprintf_s(golSettings->sGridPath, sizeof(golSettings->sGridPath), "resources/grids/grid_%d.png", golSettings->sCellsSize);
	
	*golGrid = IMG_Load(golSettings->sGridPath);

	if (*golGrid == NULL)
	{

		fprintf(stderr, "GOL_ERROR: Error while loading \"%s\" file. (Details: %s)", golSettings->sGridPath, SDL_GetError());

		exit(EXIT_FAILURE);

	}

}

void GOL_Settings_Grid_Display(
	SDL_Surface** golGrid,
	SDL_Surface** golScreen
	) {

	SDL_Rect position;

	position.x = GOL_SETTINGS_GAME_OFFSET_X;
	position.y = GOL_SETTINGS_GAME_OFFSET_Y;

	SDL_BlitSurface(*golGrid, NULL, *golScreen, &position);

}

void GOL_Settings_Size_Minus(
	GOL_Settings* golSettings
	) {

	switch (golSettings->sCellsSize)
	{

	case 8:
	{
		golSettings->sCellsSize = 5;
	}
	break;

	case 10:
	{
		golSettings->sCellsSize = 8;
	}
	break;

	case 16:
	{
		golSettings->sCellsSize = 10;
	}
	break;

	case 20:
	{
		golSettings->sCellsSize = 16;
	}
	break;

	case 32:
	{
		golSettings->sCellsSize = 20;
	}
	break;

	case 40:
	{
		golSettings->sCellsSize = 32;
	}
	break;

	case 64:
	{
		golSettings->sCellsSize = 40;
	}
	break;

	case 80:
	{
		golSettings->sCellsSize = 64;
	}
	break;

	default:
		break;

	}

}

void GOL_Settings_Size_Plus(
	GOL_Settings* golSettings
	) {

	switch (golSettings->sCellsSize)
	{

	case 5:
	{
		golSettings->sCellsSize = 8;
	}
	break;

	case 8:
	{
		golSettings->sCellsSize = 10;
	}
	break;

	case 10:
	{
		golSettings->sCellsSize = 16;
	}
	break;

	case 16:
	{
		golSettings->sCellsSize = 20;
	}
	break;

	case 20:
	{
		golSettings->sCellsSize = 32;
	}
	break;

	case 32:
	{
		golSettings->sCellsSize = 40;
	}
	break;

	case 40:
	{
		golSettings->sCellsSize = 64;
	}
	break;

	case 64:
	{
		golSettings->sCellsSize = 80;
	}
	break;

	default:
		break;

	}

}
