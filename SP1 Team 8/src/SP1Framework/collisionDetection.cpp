#include "game.h"
#include "collisionDetection.h"
#include "boxes.h"
#include "loadlevel.h"
#include "keys.h"
#include "inventory.h"
#include "doors.h"

extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern unsigned int g_levelNumber;

//Edit these 2 variables to add on or remove things that you want to NOT collide with. Their names should be rather self explainatory.
const int numberOfTouchableItems = 46;
char touchableItems[numberOfTouchableItems] = {' ', '2', '3', '4', '5', '6', '[', '}', '@', '-', '+', '$', ',', '.', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '<', '>','^','?', 'v', '!'};

void detectItemsCollision() {

	detectGoToNextLevel();
	detectRestartLevel();
	detectKeys();
	detectDoors();

}

//3 g_worldGrid values will be given as parameters, and a true or false will be returned.
//True means that the player can pass through it, and false means the player cannot.
bool collisionDetection(int a, int b, int c) {

	bool ba = false;
	bool bb = false;
	bool bc = false;

	for (int i = 0; i < numberOfTouchableItems; ++i) {
		if (a == touchableItems[i]) {
			ba = true;
			break;
		}
	}

	for (int i = 0; i < numberOfTouchableItems; ++i) {
		if (b == touchableItems[i]) {
			bb = true;
			break;
		}
	}

	for (int i = 0; i < numberOfTouchableItems; ++i) {
		if (c == touchableItems[i]) {
			bc = true;
			break;
		}
	}

	if (ba && bb && bc) {
		return true;
	} else {
		return false;
	}

}

bool playerCollisionDetectionUp() {
	
	int centerUp = g_worldGrid[charLocation.X][charLocation.Y - 3];
	int leftUp = g_worldGrid[charLocation.X - 1][charLocation.Y - 3];
	int rightUp = g_worldGrid[charLocation.X + 1][charLocation.Y - 3];

	return collisionDetection(centerUp, leftUp, rightUp);

}

bool playerCollisionDetectionDown() {

	int leftBottom = g_worldGrid[charLocation.X - 1][charLocation.Y + 1];
	int centerBottom = g_worldGrid[charLocation.X][charLocation.Y + 1];
	int rightBottom = g_worldGrid[charLocation.X + 1][charLocation.Y + 1];
	
	return collisionDetection(leftBottom, rightBottom, centerBottom);

}

bool playerCollisionDetectionLeft() {

	int upLeft = g_worldGrid[charLocation.X - 2][charLocation.Y - 2];
	int centerLeft = g_worldGrid[charLocation.X - 2][charLocation.Y - 1];
	int bottomLeft = g_worldGrid[charLocation.X - 2][charLocation.Y];

	return collisionDetection(upLeft, centerLeft, bottomLeft);

}

bool playerCollisionDetectionRight() {

	int upRight = g_worldGrid[charLocation.X + 2][charLocation.Y - 2];
	int centerRight = g_worldGrid[charLocation.X + 2][charLocation.Y - 1];
	int bottomRight = g_worldGrid[charLocation.X + 2][charLocation.Y];
	
	return collisionDetection(upRight, centerRight, bottomRight);

}

bool boxesCollisionDown(Boxes &box) {

	unsigned int leftDown = g_worldGrid[box.boxLocationX - 1][box.boxLocationY + 1];
	unsigned int centerDown = g_worldGrid[box.boxLocationX][box.boxLocationY + 1];
	unsigned int rightDown = g_worldGrid[box.boxLocationX + 1][box.boxLocationY + 1];

	return collisionDetection(leftDown, centerDown, rightDown);

}

bool boxesCollisionLeft(Boxes &box) {

	unsigned int topLeft = g_worldGrid[box.boxLocationX - 2][box.boxLocationY - 2];
	unsigned int centerLeft = g_worldGrid[box.boxLocationX - 2][box.boxLocationY - 1];
	unsigned int bottomLeft = g_worldGrid[box.boxLocationX - 2][box.boxLocationY];

	return collisionDetection(topLeft, centerLeft, bottomLeft);

}

bool boxesCollisionRight(Boxes &box) {

	unsigned int topRight = g_worldGrid[box.boxLocationX + 2][box.boxLocationY - 2];
	unsigned int centerRight = g_worldGrid[box.boxLocationX + 2][box.boxLocationY - 1];
	unsigned int bottomRight = g_worldGrid[box.boxLocationX + 2][box.boxLocationY];

	return collisionDetection(topRight, centerRight, bottomRight);

}

void detectGoToNextLevel() {

	if (g_worldGrid[charLocation.X][charLocation.Y] == '2' || g_worldGrid[charLocation.X - 1][charLocation.Y] == '2' || g_worldGrid[charLocation.X + 1][charLocation.Y] == '2') {
		++g_levelNumber;
		updateWorldGrid(g_levelNumber);
		clearInventory();
	}

}

void detectRestartLevel() {

	if (g_worldGrid[charLocation.X][charLocation.Y] == '-' || g_worldGrid[charLocation.X - 1][charLocation.Y] == '-' || g_worldGrid[charLocation.X + 1][charLocation.Y] == '-') {
		updateWorldGrid(g_levelNumber);
		clearInventory();
	}

}

void detectRestartLevel(int X , int Y) {

	if ((charLocation.X-1== X && charLocation.Y == Y) || (charLocation.X== X && charLocation.Y == Y) || (charLocation.X+1== X && charLocation.Y == Y) || (charLocation.X-1== X && charLocation.Y-1 == Y) || (charLocation.X== X && charLocation.Y-1 == Y) || (charLocation.X+1== X && charLocation.Y-1 == Y)  ||  (charLocation.X-1== X && charLocation.Y-2 == Y ) || (charLocation.X== X && charLocation.Y-2 == Y ) || (charLocation.X+1== X && charLocation.Y-2 == Y ) )  
	{
		updateWorldGrid(g_levelNumber);
		clearInventory();
	}
}