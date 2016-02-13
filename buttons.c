#include "buttons.h"

int GOL_Button_Valid_Coordinates(
	int bX,
	int bY,
	GOL_Button golButton
	) {

	if (bX >= golButton.bPosition.x && bX < (golButton.bPosition.x + GOL_BUTTONS_SIZE))
		if (bY >= golButton.bPosition.y && bY < (golButton.bPosition.y + GOL_BUTTONS_SIZE))
			return 1;

	return 0;

}

void GOL_Button_Initialisation(
	GOL_Button* golButton,
	int pipeOffset
	) {

	char iconPath[GOL_BUTTONS_ICON_PATH_LENGTH];

	golButton->bHoverState = 0;

	if (golButton->bId == B_GRID || golButton->bId == B_PENCIL)
		golButton->bFocusState = 1;
	else
		golButton->bFocusState = 0;

	sprintf_s(iconPath, GOL_BUTTONS_ICON_PATH_LENGTH, "Resources/Buttons/%d_default.png", golButton->bId);
	golButton->bIcon[0] = IMG_Load(iconPath);

	sprintf_s(iconPath, GOL_BUTTONS_ICON_PATH_LENGTH, "Resources/Buttons/%d_hover.png", golButton->bId);
	golButton->bIcon[1] = IMG_Load(iconPath);

	sprintf_s(iconPath, GOL_BUTTONS_ICON_PATH_LENGTH, "Resources/Buttons/%d_focus.png", golButton->bId);
	golButton->bIcon[2] = IMG_Load(iconPath);

	golButton->bPosition.x = (Sint16)(GOL_BUTTONS_OFFSET_X);
	golButton->bPosition.x += (Sint16)(pipeOffset * GOL_BUTTONS_PIPE_OFFSET);
	golButton->bPosition.x += (Sint16)((GOL_BUTTONS_DISTANCE + GOL_BUTTONS_SIZE) * golButton->bId);

	golButton->bPosition.y = (Sint16)(GOL_BUTTONS_OFFSET_Y);

}

int GOL_Button_MouseHover(
	GOL_Button golButton,
	int motionX,
	int motionY
	) {

	if (motionX >= golButton.bPosition.x && motionX <= (golButton.bPosition.x + GOL_BUTTONS_SIZE))
		if (motionY >= golButton.bPosition.y && motionY <= (golButton.bPosition.y + GOL_BUTTONS_SIZE))
			return 1;

	return 0;

}

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
	) {

	switch (golButton->bId)
	{

	case B_RESET:
	{

		if (!golSettings->sGenerationsAuto)
		{
			GOL_Cell_Grid_Free(golCellGrid, golSettings);
			GOL_Cell_Grid_Free(golCellGridBackup, golSettings);
			GOL_Cell_Grid_Initialisation(golCellGrid, golSettings);
			GOL_Cell_Grid_Initialisation(golCellGridBackup, golSettings);
		}

	}
	break;

	case B_BACKUP:
	{
		if (!golSettings->sGenerationsAuto)
			GOL_Cell_Grid_Assignment(golCellGrid, golCellGridBackup, golSettings);
	}
	break;

	case B_PLAY:
	{

		if (golSettings->sGenerationsAuto)
			golButton->bFocusState = 0;
		else
		{

			golButton->bFocusState = 1;

			GOL_Cell_Grid_Assignment(golCellGridBackup, golCellGrid, golSettings);

		}

		golSettings->sGenerationsAuto = 1 - golSettings->sGenerationsAuto;

	}
	break;

	case B_NEXT:
	{

		if (!golSettings->sGenerationsAuto)
		{

			GOL_Cell_Grid_Neighboors_Calculation(golCellGrid, golSettings);
			GOL_Cell_Grid_NextGen_Calculation(golCellGrid, golSettings);

		}

	}
	break;

	case B_ZOOMIN:
	{

		if (golSettings->sCellsSize < GOL_CELL_MAX_SIZE && !golSettings->sGenerationsAuto)
		{

			GOL_Cell_Grid_Free(golCellGrid, golSettings);
			GOL_Cell_Grid_Free(golCellGridBackup, golSettings);

			GOL_Settings_Size_Plus(golSettings);
			golSettings->sCellsPerLine = GOL_SETTINGS_GAME_DIMENSION / golSettings->sCellsSize;

			SDL_FreeSurface(*golGrid);

			SDL_FreeSurface(*golCellVirgin);
			SDL_FreeSurface(*golCellAlive);
			SDL_FreeSurface(*golCellDead);

			GOL_Settings_Grid_Initialisation(golGrid, golSettings);

			GOL_Cells_Initialisation(golScreen, golCellVirgin, golCellAlive, golCellDead, golSettings);

			GOL_Cell_Grid_Initialisation(golCellGrid, golSettings);
			GOL_Cell_Grid_Initialisation(golCellGridBackup, golSettings);

		}

	}
	break;

	case B_ZOOMOUT:
	{

		if (golSettings->sCellsSize > GOL_CELL_MIN_SIZE && !golSettings->sGenerationsAuto)
		{

			GOL_Cell_Grid_Free(golCellGrid, golSettings);
			GOL_Cell_Grid_Free(golCellGridBackup, golSettings);

			GOL_Settings_Size_Minus(golSettings);
			golSettings->sCellsPerLine = GOL_SETTINGS_GAME_DIMENSION / golSettings->sCellsSize;

			SDL_FreeSurface(*golGrid);

			SDL_FreeSurface(*golCellVirgin);
			SDL_FreeSurface(*golCellAlive);
			SDL_FreeSurface(*golCellDead);

			GOL_Settings_Grid_Initialisation(golGrid, golSettings);

			GOL_Cells_Initialisation(golScreen, golCellVirgin, golCellAlive, golCellDead, golSettings);

			GOL_Cell_Grid_Initialisation(golCellGrid, golSettings);
			GOL_Cell_Grid_Initialisation(golCellGridBackup, golSettings);

		}

	}
	break;

	case B_GRID:
	{

		if (golSettings->sGrid)
			golButton->bFocusState = 0;
		else
			golButton->bFocusState = 1;

		golSettings->sGrid = 1 - golSettings->sGrid;

	}
	break;

	case B_PENCIL:
	{
		golSettings->sTool = 0;
		golButton->bFocusState = 1;
		golButtonGroup->bgButtonGroup[B_BRUSH].bFocusState = 0;
	}
	break;

	case B_BRUSH:
	{
		golSettings->sTool = 1;
		golButton->bFocusState = 1;
		golButtonGroup->bgButtonGroup[B_PENCIL].bFocusState = 0;
	}
	break;

	}

}

void GOL_Button_Group_Initialisation(
	GOL_Button_Group* golButtonGroup
	) {

	int i;
	int pipeOffset = 0;

	golButtonGroup->bgButtonGroup = malloc(GOL_BUTTONS_NUMBER * sizeof(GOL_Button));

	if (golButtonGroup->bgButtonGroup == NULL)
	{

		fprintf(stderr, "GOL_ERROR: Error while allocating memory to \"golButtonGroup\".");

		exit(EXIT_FAILURE);

	}

	for (i = 0; i < GOL_BUTTONS_NUMBER; i++)
	{

		golButtonGroup->bgButtonGroup[i].bId = i;

		GOL_Button_Initialisation(&golButtonGroup->bgButtonGroup[i], pipeOffset);

		switch (golButtonGroup->bgButtonGroup[i].bId)
		{

		case B_BACKUP:
		case B_NEXT:
		case B_GRID:
		case B_BRUSH:
		{
			pipeOffset++;
		}
		break;

		}

	}

}

void GOL_Button_Group_Display(
	SDL_Surface** golScreen,
	GOL_Button_Group* golButtonGroup
	) {

	int i;

	for (i = 0; i < GOL_BUTTONS_NUMBER; i++)
		if(golButtonGroup->bgButtonGroup[i].bFocusState == 1)
			SDL_BlitSurface(golButtonGroup->bgButtonGroup[i].bIcon[2], NULL, *golScreen, &golButtonGroup->bgButtonGroup[i].bPosition);
		else if (golButtonGroup->bgButtonGroup[i].bHoverState == 1)
			SDL_BlitSurface(golButtonGroup->bgButtonGroup[i].bIcon[1], NULL, *golScreen, &golButtonGroup->bgButtonGroup[i].bPosition);
		else
			SDL_BlitSurface(golButtonGroup->bgButtonGroup[i].bIcon[0], NULL, *golScreen, &golButtonGroup->bgButtonGroup[i].bPosition);

}

void GOL_Button_Group_MouseMotionHandle(
	GOL_Button_Group* golButtonGroup,
	int motionX,
	int motionY
	) {

	int i;

	for (i = 0; i < GOL_BUTTONS_NUMBER; i++)
		if (GOL_Button_MouseHover(golButtonGroup->bgButtonGroup[i], motionX, motionY))
			golButtonGroup->bgButtonGroup[i].bHoverState = 1;
		else
			golButtonGroup->bgButtonGroup[i].bHoverState = 0;

}

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
	) {

	if (button == SDL_BUTTON_LEFT)
	{

		int i;

		for (i = 0; i < GOL_BUTTONS_NUMBER; i++)
			if (GOL_Button_Valid_Coordinates(motionX, motionY, golButtonGroup->bgButtonGroup[i]))
				GOL_Button_MouseClick(golScreen, golCellVirgin, golCellAlive, golCellDead, golGrid, golButtonGroup, &golButtonGroup->bgButtonGroup[i], golCellGrid, golCellGridBackup, golSettings);

	}

}

void GOL_Button_Group_Free(
	GOL_Button_Group* golButtonGroup
	) {

	free(golButtonGroup->bgButtonGroup);

}
