#include "game.h"
#include "teleporters.h"
#include "Framework\console.h"
#include "movecharacter.h"

extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern unsigned int g_levelNumber;
extern bool keyPressed[K_COUNT];
extern Mummy mummy;
unsigned int teleportCoolDown = 0;

void detectUseTeleporters(int teleporter1X, int teleporter1Y, int teleporter2X, int teleporter2Y) {

	g_worldGrid[teleporter1X][teleporter1Y] = '3';
   	g_worldGrid[teleporter2X][teleporter2Y] = '3';

	if (teleportCoolDown==0)
	{
		if ((charLocation.X == teleporter1X || charLocation.X - 1 == teleporter1X || charLocation.X + 1 == teleporter1X) && charLocation.Y == teleporter1Y && keyPressed[K_DOWN] && teleportCoolDown == 0 && !mummy.isGrabbing) {

			charLocation.X = teleporter2X;
			charLocation.Y = teleporter2Y;
			teleportCoolDown = 100;

		} else if ((charLocation.X == teleporter2X || charLocation.X - 1 == teleporter2X || charLocation.X + 1 == teleporter2X) && charLocation.Y == teleporter2Y && keyPressed[K_DOWN] && teleportCoolDown == 0 && !mummy.isGrabbing) {

			charLocation.X = teleporter1X;
			charLocation.Y = teleporter1Y;
			teleportCoolDown = 100;

		}
	} else 
	{
		--teleportCoolDown;
	}

}