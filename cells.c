#include "cells.h"

int GOL_Cell_Valid_Coordinates(
	int cX,
	int cY,
	GOL_Settings golSettings
	) {

	if (cX >= 0 && cX < golSettings.sCellsPerLine)
		if (cY >= 0 && cY < golSettings.sCellsPerLine)
			return 1;

	return 0;

}

int GOL_Cell_X_CoordinatesFromReal(
	int cX,
	GOL_Settings* golSettings
	) {

	return (int)floor((cX - GOL_SETTINGS_GAME_OFFSET_X) / golSettings->sCellsSize);

}

int GOL_Cell_Y_CoordinatesFromReal(
	int cY,
	GOL_Settings* golSettings
	) {

	return (int)floor((cY - GOL_SETTINGS_GAME_OFFSET_Y) / golSettings->sCellsSize);

}

void GOL_Cell_Initialisation(
	GOL_Cell* golCell,
	GOL_Settings* golSettings
	) {

	golCell->cState = VIRGIN;
	golCell->cNeighboors = 0;
	golCell->cPosition.x = (Sint16)(golCell->cX * golSettings->sCellsSize + GOL_SETTINGS_GAME_OFFSET_X);
	golCell->cPosition.y = (Sint16)(golCell->cY * golSettings->sCellsSize + GOL_SETTINGS_GAME_OFFSET_Y);

}

void GOL_Cells_Initialisation(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Settings* golSettings
	) {

	Uint32 golCellVirginColor = SDL_MapRGB((*golScreen)->format, 134, 205, 205);
	Uint32 golCellAliveColor = SDL_MapRGB((*golScreen)->format, 44, 94, 127);
	Uint32 golCellDeadColor = SDL_MapRGB((*golScreen)->format, 184, 255, 255);

	*golCellVirgin = SDL_CreateRGBSurface(SDL_HWSURFACE, golSettings->sCellsSize, golSettings->sCellsSize, 32, 0, 0, 0, 0);
	*golCellAlive = SDL_CreateRGBSurface(SDL_HWSURFACE, golSettings->sCellsSize, golSettings->sCellsSize, 32, 0, 0, 0, 0);
	*golCellDead = SDL_CreateRGBSurface(SDL_HWSURFACE, golSettings->sCellsSize, golSettings->sCellsSize, 32, 0, 0, 0, 0);

	SDL_FillRect(*golCellVirgin, NULL, golCellVirginColor);
	SDL_FillRect(*golCellAlive, NULL, golCellAliveColor);
	SDL_FillRect(*golCellDead, NULL, golCellDeadColor);

}

int GOL_Cell_Neighboors_Calculation(
	GOL_Cell golCell,
	GOL_Cell_Grid golCellGrid,
	GOL_Settings golSettings
	) {

	int i, j;
	int neighboors = 0;

	for (i = (golCell.cX - 1); i <= (golCell.cX + 1); i++)
		for (j = (golCell.cY - 1); j <= (golCell.cY + 1); j++)
			if (!(i == golCell.cX && j == golCell.cY))
				if (GOL_Cell_Valid_Coordinates(i, j, golSettings))
					if (golCellGrid.cgCellGrid[i][j].cState == ALIVE)
						neighboors++;

	return neighboors;

}

void GOL_Cell_State_Calculation(
	GOL_Cell* golCell,
	GOL_Cell* golNewCell
	) {

	switch (golCell->cNeighboors)
	{

	case 3:
	{
		golNewCell->cState = ALIVE;
	}
	break;

	case 2:
		break;

	default:
	{
		if(golNewCell->cState != VIRGIN)
			golNewCell->cState = DEAD;
	}
	break;

	}

}

void GOL_Cell_Display(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Cell* golCell
	) {

	switch (golCell->cState)
	{

	case VIRGIN:
	{
		SDL_BlitSurface(*golCellVirgin, NULL, *golScreen, &golCell->cPosition);
	}
	break;

	case ALIVE:
	{
		SDL_BlitSurface(*golCellAlive, NULL, *golScreen, &golCell->cPosition);
	}
	break;

	case DEAD:
	{
		SDL_BlitSurface(*golCellDead, NULL, *golScreen, &golCell->cPosition);
	}
	break;

	}

}

void GOL_Cell_SetAlive(
	GOL_Cell* golCell
	) {

	golCell->cState = ALIVE;

}

void GOL_Cell_SetVirgin(
	GOL_Cell* golCell
	) {

	golCell->cState = VIRGIN;

}

void GOL_Cell_Grid_MouseClickHandle(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings,
	int motionX,
	int motionY,
	Uint8 button
	) {

	if (GOL_Cell_Grid_MouseInGame(motionX, motionY))
	{

		int cX = GOL_Cell_X_CoordinatesFromReal(motionX, golSettings);
		int cY = GOL_Cell_Y_CoordinatesFromReal(motionY, golSettings);

		if (button == SDL_BUTTON_LEFT)
		{
			GOL_Cell_SetAlive(&golCellGrid->cgCellGrid[cX][cY]);
		}
		else if (button == SDL_BUTTON_RIGHT || button == SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			GOL_Cell_SetVirgin(&golCellGrid->cgCellGrid[cX][cY]);
		}

	}

}

int GOL_Cell_Grid_MouseInGame(
	int motionX,
	int motionY
	) {

	if (motionX >= GOL_SETTINGS_GAME_OFFSET_X && motionX < (GOL_SETTINGS_GAME_DIMENSION + GOL_SETTINGS_GAME_OFFSET_X))
		if (motionY >= GOL_SETTINGS_GAME_OFFSET_Y && motionY < (GOL_SETTINGS_GAME_DIMENSION + GOL_SETTINGS_GAME_OFFSET_Y))
			return 1;

	return 0;

}

void GOL_Cell_Grid_Initialisation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	int i, j;

	golCellGrid->cgCellGrid = malloc(golSettings->sCellsPerLine * sizeof(GOL_Cell*));

	if (golCellGrid->cgCellGrid == NULL)
	{

		fprintf(stderr, "GOL_ERROR: Error while allocating memory to \"golCellGrid\".");

		exit(EXIT_FAILURE);

	}

	for (i = 0; i < golSettings->sCellsPerLine; i++)
	{

		golCellGrid->cgCellGrid[i] = malloc(golSettings->sCellsPerLine * sizeof(GOL_Cell));

		if (golCellGrid->cgCellGrid[i] == NULL)
		{

			fprintf(stderr, "GOL_ERROR: Error while allocating memory to \"golCellGrid\". (cell number %d)", i);

			exit(EXIT_FAILURE);

		}

	}

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		for (j = 0; j < golSettings->sCellsPerLine; j++)
		{

			golCellGrid->cgCellGrid[i][j].cX = i;
			golCellGrid->cgCellGrid[i][j].cY = j;

			GOL_Cell_Initialisation(&golCellGrid->cgCellGrid[i][j], golSettings);

		}

}

void GOL_Cell_Grid_Neighboors_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	int i, j;

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		for (j = 0; j < golSettings->sCellsPerLine; j++)
			golCellGrid->cgCellGrid[i][j].cNeighboors = GOL_Cell_Neighboors_Calculation(golCellGrid->cgCellGrid[i][j], *golCellGrid, *golSettings);

}

void GOL_Cell_Grid_State_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Cell_Grid* golNewCellGrid,
	GOL_Settings* golSettings
	) {

	int i, j;

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		for (j = 0; j < golSettings->sCellsPerLine; j++)
			GOL_Cell_State_Calculation(&golCellGrid->cgCellGrid[i][j], &golNewCellGrid->cgCellGrid[i][j]);

}

void GOL_Cell_Grid_NextGen_Calculation(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	GOL_Cell_Grid golNewCellGrid;

	GOL_Cell_Grid_Initialisation(&golNewCellGrid, golSettings);

	GOL_Cell_Grid_Assignment(&golNewCellGrid, golCellGrid, golSettings);

	GOL_Cell_Grid_State_Calculation(golCellGrid, &golNewCellGrid, golSettings);

	GOL_Cell_Grid_Assignment(golCellGrid, &golNewCellGrid, golSettings);

	GOL_Cell_Grid_Free(&golNewCellGrid, golSettings);

}

void GOL_Cell_Grid_Assignment(
	GOL_Cell_Grid* golCellGridX,
	GOL_Cell_Grid* golCellGridY,
	GOL_Settings* golSettings
	) {

	int i, j;

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		for (j = 0; j < golSettings->sCellsPerLine; j++)
			golCellGridX->cgCellGrid[i][j] = golCellGridY->cgCellGrid[i][j];

}

void GOL_Cell_Grid_Display(
	SDL_Surface** golScreen,
	SDL_Surface** golCellVirgin,
	SDL_Surface** golCellAlive,
	SDL_Surface** golCellDead,
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	int i, j;

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		for (j = 0; j < golSettings->sCellsPerLine; j++)
			GOL_Cell_Display(golScreen, golCellVirgin, golCellAlive, golCellDead, &golCellGrid->cgCellGrid[i][j]);

}

void GOL_Cell_Grid_Free(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	int i;

	for (i = 0; i < golSettings->sCellsPerLine; i++)
		free(golCellGrid->cgCellGrid[i]);

	free(golCellGrid->cgCellGrid);

}
