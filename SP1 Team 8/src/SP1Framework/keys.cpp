#include "game.h"
#include "keys.h"
#include "inventory.h"
#include "Framework\console.h"
#include <windows.h>
#include "Music.h"
#include "printMessages.h"

extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern Console console;

//Check if the player has walked over a key.
void detectKeys()
{
	unsigned int *playerBottom[3] = {&g_worldGrid[charLocation.X][charLocation.Y],&g_worldGrid[charLocation.X - 1][charLocation.Y],&g_worldGrid[charLocation.X + 1][charLocation.Y]};

	for( unsigned int w =0 ; w<3 ; ++w)
	{
		if(*playerBottom[w]== '4')
		{
			if (inventoryManagement("Red Key", 1)) {
				*playerBottom[w] = ' ';
				printMessages("You have picked up a Red Key!");
			}
			playMusic(2);
		}
		else if(*playerBottom[w] == '5')
		{
			if (inventoryManagement("Blue Key", 1)) {
				*playerBottom[w] = ' ';
				printMessages("You have picked up a Blue Key!");
			}
			playMusic(2);
		}
		else if(*playerBottom[w] == '6')
		{
			if (inventoryManagement("Green Key", 1)) {
				*playerBottom[w] = ' ';
				printMessages("You have picked up a Green Key!");				
			}
			playMusic(2);
		}
	}

}