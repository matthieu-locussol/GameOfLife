#include "main.h"

int main(int argc, char* argv[])
{

	/*
	 * Use GOL_UNEREFERENCED_PARAMETER to avoid warnings about unused variables
	 */

	GOL_UNREFERENCED_PARAMETER(argc);
	GOL_UNREFERENCED_PARAMETER(argv);

	SDL_Event golEvent;

	SDL_Surface *golScreen = NULL;
	SDL_Surface *golBackground = NULL;
	SDL_Surface *golGrid = NULL;

	SDL_Surface* golCellVirgin = NULL;
	SDL_Surface* golCellAlive = NULL;
	SDL_Surface* golCellDead = NULL;

	GOL_Settings golSettings;

	GOL_Cell_Grid golCellGrid;
	GOL_Cell_Grid golCellGridBackup;

	GOL_Button_Group golButtonGroup;

	GOL_Initialisation();
	GOL_Screen_Initialisation(&golScreen);
	GOL_Background_Initialisation(&golBackground);

	GOL_Settings_Initialisation(&golSettings);
	GOL_Settings_Grid_Initialisation(&golGrid, &golSettings);

	GOL_Cells_Initialisation(&golScreen, &golCellVirgin, &golCellAlive, &golCellDead, &golSettings);

	GOL_Cell_Grid_Initialisation(&golCellGrid, &golSettings);
	GOL_Cell_Grid_Initialisation(&golCellGridBackup, &golSettings);

	GOL_Button_Group_Initialisation(&golButtonGroup);

	while (golSettings.sRun)
	{

		while (SDL_PollEvent(&golEvent))
		{

			switch (golEvent.type)
			{

			case SDL_QUIT:
			{
				golSettings.sRun = 0;
			}
			break;

			case SDL_MOUSEMOTION:
			{
				GOL_Button_Group_MouseMotionHandle(&golButtonGroup, golEvent.motion.x, golEvent.motion.y);
				if(golSettings.sTool)
					GOL_Cell_Grid_MouseClickHandle(&golCellGrid, &golSettings, golEvent.motion.x, golEvent.motion.y, golEvent.button.button);
			}
			break;

			case SDL_MOUSEBUTTONUP:
			{
				GOL_Button_Group_MouseClickHandle(&golScreen, &golCellVirgin, &golCellAlive, &golCellDead, &golGrid, &golButtonGroup, &golCellGrid, &golCellGridBackup, &golSettings, golEvent.motion.x, golEvent.motion.y, golEvent.button.button);
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				GOL_Cell_Grid_MouseClickHandle(&golCellGrid, &golSettings, golEvent.motion.x, golEvent.motion.y, golEvent.button.button);
			}
			break;

			case SDL_KEYDOWN:
			{

				switch (golEvent.key.keysym.sym)
				{

				case SDLK_F1:
				{
					setSchema_VerticalLine(&golCellGrid, &golSettings);
				}
				break;

				case SDLK_F2:
				{
					setSchema_HorizontalLine(&golCellGrid, &golSettings);
				}
				break;

				case SDLK_F3:
				{
					setSchema_TopLeftBotRightLine(&golCellGrid, &golSettings);
				}
				break;

				case SDLK_F4:
				{
					setSchema_TopRightBotLeftLine(&golCellGrid, &golSettings);
				}
				break;

				default:
					break;

				}

			}
			break;

			default:
				break;

			}

		}

		/*
		 * Surfaces blitting
		 */

		SDL_FillRect(golScreen, NULL, SDL_MapRGB(golScreen->format, 255, 255, 255));

		SDL_BlitSurface(golBackground, NULL, golScreen, NULL);

		GOL_Cell_Grid_Display(&golScreen, &golCellVirgin, &golCellAlive, &golCellDead, &golCellGrid, &golSettings);

		GOL_Button_Group_Display(&golScreen, &golButtonGroup);

		if (golSettings.sGrid)
			GOL_Settings_Grid_Display(&golGrid, &golScreen);

		SDL_Flip(golScreen);

		/*
		* Timed actions execution
		*/

		golSettings.sTimeElapsed = SDL_GetTicks();

		if (golSettings.sTimeElapsed - golSettings.sPreviousTimeElapsed > (1000 / GOL_SETTINGS_FPS))
		{

			if (golSettings.sGenerationsAuto)
			{

				GOL_Cell_Grid_Neighboors_Calculation(&golCellGrid, &golSettings);
				GOL_Cell_Grid_NextGen_Calculation(&golCellGrid, &golSettings);

			}

			golSettings.sPreviousTimeElapsed = golSettings.sTimeElapsed;

		}

		else
		{

			SDL_Delay((1000 / GOL_SETTINGS_FPS) - (golSettings.sTimeElapsed - golSettings.sPreviousTimeElapsed));

		}

	}

	GOL_Quit(golBackground, golGrid, golCellVirgin, golCellAlive, golCellDead, &golCellGrid, &golButtonGroup, &golSettings);

	return EXIT_SUCCESS;

}

void GOL_Initialisation(
	void
	) {

	/*
	* Exit the program if we can't set "SDL_VIDEO_CENTERED" to 1.
	*/

	if (_putenv("SDL_VIDEO_CENTERED=1") != 0)
	{

		fprintf(stderr, "GOL_ERROR: Error while modifying \"SDL_VIDEO_CENTERED\" environment variable.");

		exit(EXIT_FAILURE);

	}

	/*
	* Exit the program if we can't load the SDL.
	*/

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{

		fprintf(stderr, "GOL_ERROR: Error while initializing SDL. (Details: %s)", SDL_GetError());

		exit(EXIT_FAILURE);

	}

	SDL_WM_SetCaption(GOL_WINDOW_TITLE, NULL);

}

void GOL_Screen_Initialisation(
	SDL_Surface** golScreen
	) {

	*golScreen = SDL_SetVideoMode(GOL_WINDOW_WIDTH, GOL_WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (*golScreen == NULL)
	{

		fprintf(stderr, "GOL_ERROR: Error while setting video mode. (Details: %s)", SDL_GetError());

		exit(EXIT_FAILURE);

	}

}

void GOL_Background_Initialisation(
	SDL_Surface** golBackground
	) {

	*golBackground = IMG_Load("Resources/background.png");

	/*
	* Exit the program if we can't load the background.
	*/

	if (*golBackground == NULL)
	{

		fprintf(stderr, "GOL_ERROR: Error while loading \"background.png\" file. (Details: %s)", SDL_GetError());

		exit(EXIT_FAILURE);

	}

}

void GOL_Quit(
	SDL_Surface* golBackground,
	SDL_Surface* golGrid,
	SDL_Surface* golCellVirgin,
	SDL_Surface* golCellAlive,
	SDL_Surface* golCellDead,
	GOL_Cell_Grid* golCellGrid,
	GOL_Button_Group* golButtonGroup,
	GOL_Settings* golSettings
	) {

	SDL_FreeSurface(golBackground);
	SDL_FreeSurface(golGrid);

	SDL_FreeSurface(golCellVirgin);
	SDL_FreeSurface(golCellAlive);
	SDL_FreeSurface(golCellDead);

	GOL_Cell_Grid_Free(golCellGrid, golSettings);

	GOL_Button_Group_Free(golButtonGroup);

	SDL_Quit();

}
