#include "game.h"
#include "inventory.h"
#include "keys.h"
#include "Framework\console.h"
#include "doors.h"
#include "Music.h"
#include "printMessages.h"

extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern string inventoryItems[inventorySize];
extern Console console;

//Check if we are at a door and have the needed key.
void detectDoors()
{
	unsigned int *playerBottom[2] ={&g_worldGrid[charLocation.X - 2][charLocation.Y], &g_worldGrid[charLocation.X + 2][charLocation.Y]};
	
	for (unsigned int i = 0; i < 2; i++)
	{
		if (*playerBottom[i] == '7' && hasTheRightKey("Red Key"))
		{
			removeDoor(i);

			inventoryManagement("Red Key", 0);
			playMusic(3);
			printMessages("You have opened a Red Door!");
			break;
		}
		else if (*playerBottom[i] == '8' && hasTheRightKey("Blue Key"))
		{	
			removeDoor(i);

			inventoryManagement("Blue Key", 0);
			printMessages("You have opened a Blue Door!");
			playMusic(3);
			break;
		}
		
		else if (*playerBottom[i]== '9'&& hasTheRightKey("Green Key"))
		{
			removeDoor(i);

			inventoryManagement("Green Key", 0);
			printMessages("You have opened a Green Door!");
			playMusic(3);
			break;
		}
	}
}

bool hasTheRightKey(string key)
{
	for(int i =0 ; i<inventorySize ; ++i)
	{
		if(inventoryItems[i] == key)
		{
			return true;
		}
	}
	return false;
}

void removeDoor(unsigned int h) {

	//If the doors are on the left of the player.
	if (h == 0) 
	{
		//Set the coordinates where the doors were to nothing.
		g_worldGrid[charLocation.X - 2][charLocation.Y] = ' ';
		g_worldGrid[charLocation.X - 2][charLocation.Y - 1] = ' ';
		g_worldGrid[charLocation.X - 2][charLocation.Y - 2] = ' ';
	}
	//If the doors are on the right of the player.
	else if (h == 1) 
	{
		//Set the coordinates where the doors were to nothing.
		g_worldGrid[charLocation.X + 2][charLocation.Y] = ' ';
		g_worldGrid[charLocation.X + 2][charLocation.Y - 1] = ' ';
		g_worldGrid[charLocation.X + 2][charLocation.Y - 2] = ' ';
	}

}