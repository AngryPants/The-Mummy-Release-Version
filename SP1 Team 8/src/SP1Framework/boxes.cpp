#include "game.h"
#include "boxes.h"
#include "collisionDetection.h"
#include "Framework\console.h"
#include "movecharacter.h"

//External Variables
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern Console console;
extern COORD charLocation;
extern Mummy mummy;

//Local Variables
//This is a vector that will store all the boxes that were spawned in a level. It is cleared at the start of every level for new boxes to be spawned.
vector<Boxes> boxes;
//Things that the box can collide into but NOT destroy.
const unsigned int numberOfNonDestructibleItems = 34;
char canCollideCannotDestroy[numberOfNonDestructibleItems] = {'4', '5', '6', '2', '^', 'v', '<', '>', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J,', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//This is the box that is currently being held by the player.
Boxes *g_heldBox = 0;

void boxesUpdate() {

	for (unsigned int i = 0; i < boxes.size(); ++i) {
		
		//This is an array which stores the coordinates of the box(which takes up 9 spaces)
		unsigned int * boxCoords[9] = {
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY - 2],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY - 2],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY - 2]
		};

		//This is to delete everything that the box is overlaping with, such as lava.
		for (unsigned int h = 0; h < 9; ++h) {
			if (canDestroy(*boxCoords[h])) {
				*boxCoords[h] = ' ';
			}
		}

		//This makes the box fall down if there is no ground underneath it.
		boxesGravity(boxes[i]);
		
		//This is to move the box if a player is pushing/pulling it.
		moveBox(boxes[i]);

		//If the box is no longer the same Y coordinates as the player, the box is released if the player was holding it.
		if (mummy.isGrabbing && g_heldBox->boxLocationY != charLocation.Y) {
			releaseBox(*g_heldBox);
		}

		//A new array to get the new coordinates of the box as the box has been moved.
		unsigned int * boxCoordsNew[9] = {
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY],
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY - 1],
			&g_worldGrid[boxes[i].boxLocationX][boxes[i].boxLocationY - 2],
			&g_worldGrid[boxes[i].boxLocationX - 1][boxes[i].boxLocationY - 2],
			&g_worldGrid[boxes[i].boxLocationX + 1][boxes[i].boxLocationY - 2]
		};

		//This is to 'solidify' the box so that the player and other boxes cannot pass through it.
		for (unsigned int h = 0; h < 9; ++h) {
			if (canDestroy(*boxCoordsNew[h])) {
				*boxCoordsNew[h] = '%';
			}
		}

	}

}

void spawnBoxes(unsigned int boxSpawnX, unsigned int boxSpawnY, string boxColour) {

	Boxes newBox;

	newBox.boxLocationX = boxSpawnX;
	newBox.boxLocationY = boxSpawnY;
	newBox.beingHeldRight = false;
	newBox.beingHeldLeft = false;

	if (boxColour == "Yellow") {
		newBox.boxColour = 0x6E;
		newBox.gravityDirection = 1;
		newBox.isMovable = true;
	} else if (boxColour == "Purple") {
		newBox.boxColour = 0x5D;
		newBox.gravityDirection = 0;
		newBox.isMovable = true;
	} else if (boxColour == "Grey") {
		newBox.boxColour = 0x08;
		newBox.gravityDirection = 1;
		newBox.isMovable = false;
	}

	boxes.push_back(newBox);

}

void boxesGravity(Boxes &box) {

	if (boxesCollisionDown(box) && box.gravityDirection == 1) {
		++box.boxLocationY;
	} else if (boxesCollisionUp(box) && box.gravityDirection == 0) {
		--box.boxLocationY;
	}

}

bool boxesCollisionUp(Boxes &box) {

	unsigned int leftUp = g_worldGrid[box.boxLocationX - 1][box.boxLocationY - 3];
	unsigned int centerUp = g_worldGrid[box.boxLocationX][box.boxLocationY - 3];
	unsigned int rightUp = g_worldGrid[box.boxLocationX + 1][box.boxLocationY - 3];

	return collisionDetection(leftUp, centerUp, rightUp);

}

void grabBox(collisionDirection direction) {

	//If the box is on the right side of the player.
	if (direction == Right) {
		for (unsigned int i = 0; i < boxes.size(); ++i) {
			if (boxes[i].boxLocationY == charLocation.Y && boxes[i].boxLocationX == charLocation.X + 3 && boxes[i].isMovable) {
				boxes[i].beingHeldRight = true;
				boxes[i].beingHeldLeft = false;
				mummy.isGrabbing = true;
				g_heldBox = &boxes[i];
				break;
			}
		}
	//If the box is on the left side of the player.
	} else if (direction == Left) {
		for (unsigned int i = 0; i < boxes.size(); ++i) {
			if (boxes[i].boxLocationY == charLocation.Y && boxes[i].boxLocationX == charLocation.X - 3 && boxes[i].isMovable) {
				boxes[i].beingHeldRight = false;
				boxes[i].beingHeldLeft = true;
				mummy.isGrabbing = true;
				g_heldBox = &boxes[i];
				break;
			}
		}
	}

}

void moveBox(Boxes &box) {

	if (box.beingHeldLeft == true && charLocation.Y == box.boxLocationY) {
		box.boxLocationX = charLocation.X - 3;
	} else if (box.beingHeldRight == true  && charLocation.Y == box.boxLocationY) {
		box.boxLocationX = charLocation.X + 3;
	}

}

//Release all the boxes.
void releaseBox() {

	for (unsigned int i = 0; i < boxes.size(); ++i) {
		boxes[i].beingHeldLeft = false;
		boxes[i].beingHeldRight = false;
		mummy.isGrabbing = false;
	}

}

//Release a specific box.
void releaseBox(Boxes &box) {

	box.beingHeldLeft = false;
	box.beingHeldRight = false;
	mummy.isGrabbing = false;

}

//Checks if the box can erase the item. For example, lava can be erased, but keys cannot.
bool canDestroy(unsigned int &j) {

	for (unsigned int n = 0; n < numberOfNonDestructibleItems; ++n) {
		if (j == canCollideCannotDestroy[n]) {
			return false;
			break;
		}
	}

	return true;

}