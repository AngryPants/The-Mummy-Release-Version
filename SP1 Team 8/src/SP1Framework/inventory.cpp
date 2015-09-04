#include "game.h"
#include "Framework\console.h"
#include "printMessages.h"
#include "inventory.h"
#include "keys.h"

string inventoryItems[inventorySize] = {"Empty","Empty","Empty"};
extern Console console;

bool inventoryManagement(string item, char useOrPickUp) //For useOrPickUp, 0 means use and 1 means pick up.
{
	//If we are using a key.
	if(useOrPickUp == 0) 
	{
		for(int i = 0 ; i < inventorySize; ++i) 
		{
			//Checks if we have the key we need.
			if(inventoryItems[i] == item)
			{
				inventoryItems[i] = "Empty";
				return true;
				break;
			}
		}
	} 
	//If we are picking up a key.
	else if (useOrPickUp == 1) 
	{
		for(int j = 0; j < inventorySize; ++j) 
		{
			//Checks if the key ring has empty space.
			if(inventoryItems[j] == "Empty") 
			{
				inventoryItems[j] = item;
				return true;
				break;
			} else if (j == inventorySize - 1) {
				printMessages("Your Key Ring is full.");
				return false;
			}
		}
	}
}

//Delete all the items in the inventory.
void clearInventory()
{
	for(int k = 0; k < inventorySize; ++k)
	{
		inventoryItems[k] = "Empty";
	}
}