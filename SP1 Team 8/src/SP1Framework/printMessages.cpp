#include "printMessages.h"
#include "Framework\console.h"
#include "game.h"
#include "camera.h"

//External Variables
extern Console console;
extern int cameraSize[2];

//Local Variables
unsigned int emptyLine = 0;
//The default values of the message array.
string messageArray[messageArraySize] = {" "," "," ", " "};

void printMessages(string message)
{
	for(unsigned int a = 0;a < messageArraySize; ++a)
	{
		//If the messageArray has an empty slot, the message goes there.
		if (messageArrayHasEmptySpace()) 
		{
			messageArray[emptyLine] = message;
			break;
		} 
		else 
		{
			//Otherwise, delete the first message, scroll the rest upwards, and put the new message at the bottom slot.
			for (unsigned int w = 1; w < messageArraySize; ++w) 
			{
				messageArray[w - 1] = messageArray[w];
			}

			messageArray[messageArraySize - 1] = message;
			break;

		}
	}
}

//Checks if the messageArray has an empty space.
bool messageArrayHasEmptySpace()
{
	for(unsigned int a = 0; a < messageArraySize; a++)
	{
		if (messageArray[a] == " ") 
		{
			emptyLine = a;
			return true;
		}
	}

	return false;
}

//Render the message every frame.
void renderMessages() 
{

	int textColour = 0x0F;

	for (unsigned int v = 0; v < messageArraySize; ++v) 
	{
		if (v != emptyLine) 
		{
			textColour = 0x08;
		} 
		else 
		{
			textColour = 0x0F;
		}

		console.writeToBuffer(30, cameraSize[1] + 3 + v, messageArray[v], textColour);
	}

}