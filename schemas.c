#include "schemas.h"

void setSchema_VerticalLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	if (!golSettings->sGenerationsAuto)
	{
		int i, j;
		for (i = 0; i < golSettings->sCellsPerLine; i++)
			for (j = 0; j < golSettings->sCellsPerLine; j++)
				if (golCellGrid->cgCellGrid[i][j].cX == (golSettings->sCellsPerLine / 2 - 1) || golCellGrid->cgCellGrid[i][j].cX == (golSettings->sCellsPerLine / 2))
					GOL_Cell_SetAlive(&golCellGrid->cgCellGrid[i][j]);
	}

}

void setSchema_HorizontalLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	if (!golSettings->sGenerationsAuto)
	{
		int i, j;
		for (i = 0; i < golSettings->sCellsPerLine; i++)
			for (j = 0; j < golSettings->sCellsPerLine; j++)
				if (golCellGrid->cgCellGrid[i][j].cY == (golSettings->sCellsPerLine / 2 - 1) || golCellGrid->cgCellGrid[i][j].cY == (golSettings->sCellsPerLine / 2))
					GOL_Cell_SetAlive(&golCellGrid->cgCellGrid[i][j]);
	}

}

void setSchema_TopLeftBotRightLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	if (!golSettings->sGenerationsAuto)
	{
		int i, j;
		for (i = 0; i < golSettings->sCellsPerLine; i++)
			for (j = 0; j < golSettings->sCellsPerLine; j++)
				if (golCellGrid->cgCellGrid[i][j].cX == golCellGrid->cgCellGrid[i][j].cY)
					GOL_Cell_SetAlive(&golCellGrid->cgCellGrid[i][j]);
	}

}

void setSchema_TopRightBotLeftLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	) {

	if (!golSettings->sGenerationsAuto)
	{
		int i, j;
		for (i = 0; i < golSettings->sCellsPerLine; i++)
			for (j = 0; j < golSettings->sCellsPerLine; j++)
				if (golCellGrid->cgCellGrid[i][j].cX == (golSettings->sCellsPerLine - golCellGrid->cgCellGrid[i][j].cY - 1))
					GOL_Cell_SetAlive(&golCellGrid->cgCellGrid[i][j]);
	}

}
