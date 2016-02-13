#ifndef DEF_SCHEMAS
#define DEF_SCHEMAS

#include <stdio.h>

#include "settings.h"
#include "cells.h"
#include "schemas.h"

void setSchema_VerticalLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void setSchema_HorizontalLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void setSchema_TopLeftBotRightLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

void setSchema_TopRightBotLeftLine(
	GOL_Cell_Grid* golCellGrid,
	GOL_Settings* golSettings
	);

#endif
