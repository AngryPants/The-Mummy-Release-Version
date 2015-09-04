#include "game.h"
#include "buttons.h"
#include "Framework\console.h"

//External Variables
extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern Console console;

void detectButtonActivated(unsigned int buttonCoordsX, unsigned int buttonCoordsY, unsigned int wallCoordsX1, unsigned int wallCoordsY1, unsigned int wallCoordsX2, unsigned int wallCoordsY2, unsigned int wallCoordsX3, unsigned int wallCoordsY3) {

	//Check if the player is stepping on the button.
	if (checkForPlayer(buttonCoordsX, buttonCoordsY)) {

		//Makes the wall open.
		g_worldGrid[wallCoordsX1][wallCoordsY1] = ' ';
		g_worldGrid[wallCoordsX2][wallCoordsY2] = ' ';
		g_worldGrid[wallCoordsX3][wallCoordsY3] = ' ';

	//Checks if a box is on the button.
	} else if (g_worldGrid[buttonCoordsX][buttonCoordsY] == '%') {

		//Makes the wall open.
		g_worldGrid[wallCoordsX1][wallCoordsY1] = ' ';
		g_worldGrid[wallCoordsX2][wallCoordsY2] = ' ';
		g_worldGrid[wallCoordsX3][wallCoordsY3] = ' ';

	} else {

		//Makes the wall close.
		g_worldGrid[wallCoordsX1][wallCoordsY1] = '1';
		g_worldGrid[wallCoordsX2][wallCoordsY2] = '1';
		g_worldGrid[wallCoordsX3][wallCoordsY3] = '1';

	}

	g_worldGrid[buttonCoordsX][buttonCoordsY] = '}';

}

bool checkForPlayer(unsigned int buttonCoordsX, unsigned int buttonCoordsY) {

	if ((charLocation.X == buttonCoordsX || charLocation.X - 1 == buttonCoordsX || charLocation.X + 1 == buttonCoordsX) && (charLocation.Y == buttonCoordsY || charLocation.Y - 1 == buttonCoordsY || charLocation.Y - 2 == buttonCoordsY)) {
		return true;
	} else {
		return false;
	}

}