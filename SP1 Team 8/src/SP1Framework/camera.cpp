#include "game.h"
#include "Framework\console.h"
#include "boxes.h"
#include "monster.h"
#include "shooter.h"
#include <iostream>
#include <iomanip>
#include <vector>

//External Variables
extern string inventoryItems[3];
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern unsigned int g_longestX;
extern unsigned int g_shortestX;
extern unsigned int g_longestY;
extern unsigned int g_shortestY;
extern COORD charLocation;
extern Console console;
extern vector<Boxes> boxes;
extern vector<MonsterLR> monsterLR;
extern vector<MonsterUD> monsterUD;
extern vector<Shooter> bullets;

//Local Variables
COORD cameraPosition;
int cameraSize[2] = {100, 30};
int distanceFromCamX = 0;
int distanceFromCamY = 0;
int distanceFromEdgeX = 27;
int screenOffSet = 1;
unsigned int timeStoodStill = 60;
char bodyParts[5] = {' ', '|', '\\', '/', (char)1};
char worldBlocks[16] = {0 /*Nothingness*/, 178 /*Walls*/, 219 /*Portal to next level*/, 232 /*Teleporter*/, 199, 199, 199 /*Keys*/, 176, 176, 176 /*Doors*/, 234 /*Poisonous Bugs*/, 177, 177, 177 /*Boxes*/, 220 /*Buttons*/, 247};
char msG[30] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 60, 62, 94};
//2D array to store the position of the walls and items etc.


void moveCameraTo() {

	distanceFromCamX = charLocation.X - cameraPosition.X + screenOffSet;
	distanceFromCamY = charLocation.Y - cameraPosition.Y + screenOffSet;

	//Moving the camera along the X-axis.
	if (distanceFromCamX < distanceFromEdgeX && cameraPosition.X > g_shortestX) {
		--cameraPosition.X;
	}
	
	if (distanceFromCamX > (cameraSize[0] - distanceFromEdgeX) && (cameraPosition.X + cameraSize[0]) < g_longestX) {
		++cameraPosition.X;
	}
	
	if (cameraPosition.X < 0) {
		cameraPosition.X = 0;
	} else if ((cameraPosition.X + cameraSize[0] > g_longestX) && g_longestX > cameraSize[0]) {
		cameraPosition.X = g_longestX - cameraSize[0];
	}

	if (timeStoodStill > 0) {
		--timeStoodStill;
	} else if (timeStoodStill == 0) {
		if (distanceFromCamX < cameraSize[0]/2 && cameraPosition.X > g_shortestX) {
			--cameraPosition.X;
		} else if (distanceFromCamX > cameraSize[0]/2 && (cameraPosition.X + cameraSize[0]) < g_longestX) {
			++cameraPosition.X;
		}
	}

	//Changing the Y position of the camera.
	if (cameraSize[1] >= g_longestY - g_shortestY) {
		cameraPosition.Y = g_shortestY;
	} else {
	
		if (distanceFromCamY < 15 && cameraPosition.Y > g_shortestY) {
			--cameraPosition.Y;
		} else if (distanceFromCamY > (cameraSize[1] - 6)) {
			++cameraPosition.Y;
		}

		if (cameraPosition.Y <= g_shortestY) {
			cameraPosition.Y = g_shortestY;
		}

		if (cameraPosition.Y + cameraSize[1] > g_longestY) {
			cameraPosition.Y = g_longestY - cameraSize[1];
		}

	}

}

void renderView() {

	for (unsigned int x = screenOffSet; x < cameraSize[0] + screenOffSet; ++x) {
		for (unsigned int y = screenOffSet; y < cameraSize[1] + screenOffSet; ++y) {

			//Scan through the array and see what we need to render in the camera.
			switch (g_worldGrid[cameraPosition.X + x - screenOffSet][cameraPosition.Y + y - screenOffSet]) {

				case '1':
					console.writeToBuffer(x, y, worldBlocks[1], 0x07);
					break;

				case '2':
					console.writeToBuffer(x, y, worldBlocks[2], 0x06);
					console.writeToBuffer(x, y - 1, worldBlocks[2], 0x06);
					console.writeToBuffer(x, y - 2, worldBlocks[2], 0x06);
					break;

				case '3':
					console.writeToBuffer(x, y, worldBlocks[3], 0x03);
					console.writeToBuffer(x, y - 1, worldBlocks[3], 0x03);
					console.writeToBuffer(x, y - 2, worldBlocks[3], 0x03);
					console.writeToBuffer(x-1, y, worldBlocks[3], 0x03);
					console.writeToBuffer(x-1, y - 1, worldBlocks[3], 0x03);
					console.writeToBuffer(x-1, y - 2, worldBlocks[3], 0x03);
					console.writeToBuffer(x+1, y, worldBlocks[3], 0x03);
					console.writeToBuffer(x+1, y - 1, worldBlocks[3], 0x03);
					console.writeToBuffer(x+1, y - 2, worldBlocks[3], 0x03);
					break;

				case '4':
					console.writeToBuffer(x, y, worldBlocks[4], 0x0C);
					break;

				case '5':
					console.writeToBuffer(x, y, worldBlocks[5], 0x09);
					break;

				case '6':
					console.writeToBuffer(x, y, worldBlocks[6], 0x0A);
					break;

				case '7':
					console.writeToBuffer(x, y, worldBlocks[7], 0x0C);
					console.writeToBuffer(x, y - 2, worldBlocks[7], 0x0C);
					console.writeToBuffer(x, y - 1, worldBlocks[7], 0x0C);
					break;

				case '8':
					console.writeToBuffer(x, y, worldBlocks[8], 0x09);
					console.writeToBuffer(x, y - 1, worldBlocks[8], 0x09);
					console.writeToBuffer(x, y - 2, worldBlocks[8], 0x09);
					break;

				case '9':
					console.writeToBuffer(x, y, worldBlocks[9], 0x0A);
					console.writeToBuffer(x, y - 1, worldBlocks[9], 0x0A);
					console.writeToBuffer(x, y - 2, worldBlocks[9], 0x0A);
					break;
				case '[':
					console.writeToBuffer(x, y, worldBlocks[10], 0x0C);
					break;

				case ']':
					console.writeToBuffer(x, y, worldBlocks[11], 0x06);
					break;

				case '}':
					console.writeToBuffer(x, y, worldBlocks[13], 0x04);
					break;

				case '-':
					console.writeToBuffer(x, y, worldBlocks[15], 0x0C);
					break;

				case 'A':
					console.writeToBuffer(x, y, msG[0], 0x0B);
					break;
				case 'B':
					console.writeToBuffer(x, y, msG[1], 0x0B);
					break;
				case 'C':
					console.writeToBuffer(x, y, msG[2], 0x0B);
					break;
				case 'D':
					console.writeToBuffer(x, y, msG[3], 0x0B);
					break;
				case 'E':
					console.writeToBuffer(x, y, msG[4], 0x0B);
					break;
				case 'F':
					console.writeToBuffer(x, y, msG[5], 0x0B);
					break;
				case 'G':
					console.writeToBuffer(x, y, msG[6], 0x0B);
					break;
				case 'H':
					console.writeToBuffer(x, y, msG[7], 0x0B);
					break;
				case 'I':
					console.writeToBuffer(x, y, msG[8], 0x0B);
					break;
				case 'J':
					console.writeToBuffer(x, y, msG[9], 0x0B);
					break;
				case 'K':
					console.writeToBuffer(x, y, msG[10], 0x0B);
					break;
				case 'L':
					console.writeToBuffer(x, y, msG[11], 0x0B);
					break;
				case 'M':
					console.writeToBuffer(x, y, msG[12], 0x0B);
					break;
				case 'N':
					console.writeToBuffer(x, y, msG[13], 0x0B);
					break;
				case 'O':
					console.writeToBuffer(x, y, msG[14], 0x0B);
					break;
				case 'P':
					console.writeToBuffer(x, y, msG[15], 0x0B);
					break;
				case 'Q':
					console.writeToBuffer(x, y, msG[16], 0x0B);
					break;
				case 'R':
					console.writeToBuffer(x, y, msG[17], 0x0B);
					break;
				case 'S':
					console.writeToBuffer(x, y, msG[18], 0x0B);
					break;
				case 'T':
					console.writeToBuffer(x, y, msG[19], 0x0B);
					break;
				case 'U':
					console.writeToBuffer(x, y, msG[20], 0x0B);
					break;
				case 'V':
					console.writeToBuffer(x, y, msG[21], 0x0B);
					break;
				case 'W':
					console.writeToBuffer(x, y, msG[22], 0x0B);
					break;
				case 'X':
					console.writeToBuffer(x, y, msG[23], 0x0B);
					break;
				case 'Y':
					console.writeToBuffer(x, y, msG[24], 0x0B);
					break;
				case 'Z':
					console.writeToBuffer(x, y, msG[25], 0x0B);
					break;
				case '!':
					console.writeToBuffer(x, y, msG[26], 0x0B);
					break;
				case '<':
					console.writeToBuffer(x, y, msG[27], 0x0B);
					break;
				case '>':
					console.writeToBuffer(x, y, msG[28], 0x0B);
					break;
				case '^':
					console.writeToBuffer(x, y, msG[29], 0x0B);
					break;
				case 'v':
					console.writeToBuffer(x, y, 'v', 0x0B);
					break;
			}

		}
	}

	for (int x = 0; x < cameraSize[0] + 2; ++x) {
		console.writeToBuffer(x, cameraSize[1] + 2, '-', 0x08);
		console.writeToBuffer(x, cameraSize[1] + 9, '-', 0x08);
		console.writeToBuffer(x, cameraSize[1] + 1, '-', 0x08);
		console.writeToBuffer(x, 0, '-', 0x08);
	}
	for (int i = 0; i <= cameraSize[1]; ++i) {
		console.writeToBuffer(cameraSize[0] + 1, i, '|', 0x08);
		console.writeToBuffer(0, i, '|', 0x08);
	}
	
	//Seperates the lines that seperates the camera and the Inventory, Messages etc.
	for (int y = 0; y < 6; ++y) {

		console.writeToBuffer(0, cameraSize[1] + y + 3, 186, 0x08);
		console.writeToBuffer(18, cameraSize[1]  + y + 3, 186, 0x08);
		console.writeToBuffer(0, cameraSize[1]  + y + 3, 186, 0x08);
		console.writeToBuffer(101, cameraSize[1] + y + 3, 186, 0x08);
		
	}

	//Render inventory.
	console.writeToBuffer(3, cameraSize[1] + 3, "Key Ring:", 0x08);
	console.writeToBuffer(3, cameraSize[1] + 4, inventoryItems[0], 0x08);
	console.writeToBuffer(3, cameraSize[1] + 5, inventoryItems[1], 0x08);
	console.writeToBuffer(3, cameraSize[1] + 6, inventoryItems[2], 0x08);

}

void renderCharacter(char direction) {
	
	//Only render the character if it is within the camera's view.
	if (distanceFromCamX > 0 && distanceFromCamX < cameraSize[0] && distanceFromCamY > 0 && distanceFromCamY < cameraSize[1]) {
		//If character is not facing left or right.
		if (direction == 0) {
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY, bodyParts[3], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY, bodyParts[2], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 1, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 1, bodyParts[1], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 1, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 2, bodyParts[2], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 2, bodyParts[4], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 2, bodyParts[3], 0x0F);
		//If character is facing left.
		} else if (direction == 1) {
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY, bodyParts[3], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY, bodyParts[1], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 1, bodyParts[3], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 1, bodyParts[1], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 1, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 2, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 2, bodyParts[4], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 2, bodyParts[0], 0x0F);
		//If character is facing right.
		} else if (direction == 2) {
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY, bodyParts[1], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY, bodyParts[2], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 1, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 1, bodyParts[1], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 1, bodyParts[2], 0x0F);
			console.writeToBuffer(distanceFromCamX - 1, distanceFromCamY - 2, bodyParts[0], 0x0F);
			console.writeToBuffer(distanceFromCamX, distanceFromCamY - 2, bodyParts[4], 0x0F);
			console.writeToBuffer(distanceFromCamX + 1, distanceFromCamY - 2, bodyParts[0], 0x0F);
		}
	}

}

void renderBoxes() {

	for (int i = 0; i < boxes.size(); ++i) {

		int boxDistanceFromCameraX = boxes[i].boxLocationX - cameraPosition.X + screenOffSet;
		int boxDistanceFromCameraY = boxes[i].boxLocationY - cameraPosition.Y + screenOffSet;

		if (boxes[i].boxLocationX >= cameraPosition.X && boxes[i].boxLocationX <= cameraPosition.X + cameraSize[0] && boxes[i].boxLocationY >= cameraPosition.Y && boxes[i].boxLocationY <= cameraPosition.Y + cameraSize[1]) {

			console.writeToBuffer(boxDistanceFromCameraX, boxDistanceFromCameraY, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX - 1, boxDistanceFromCameraY, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX + 1, boxDistanceFromCameraY, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX, boxDistanceFromCameraY - 1, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX - 1, boxDistanceFromCameraY - 1, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX + 1, boxDistanceFromCameraY - 1, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX, boxDistanceFromCameraY - 2, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX - 1, boxDistanceFromCameraY - 2, 177, boxes[i].boxColour);
			console.writeToBuffer(boxDistanceFromCameraX + 1, boxDistanceFromCameraY - 2, 177, boxes[i].boxColour);

		}

	}

}

void renderMonsters() {

	for (int i = 0; i < monsterUD.size(); ++i) {

		int monsterDistanceFromCameraX = monsterUD[i].X - cameraPosition.X + screenOffSet;
		int monsterDistanceFromCameraY = monsterUD[i].Y - cameraPosition.Y + screenOffSet;

		if (monsterUD[i].X >= cameraPosition.X && monsterUD[i].X <= cameraPosition.X + cameraSize[0] && monsterUD[i].Y >= cameraPosition.Y && monsterUD[i].Y <= cameraPosition.Y + cameraSize[1]) {

			console.writeToBuffer(monsterDistanceFromCameraX, monsterDistanceFromCameraY, 234, 0x06);

		}

	}

	for (int i = 0; i < monsterLR.size(); ++i) {

		int monsterDistanceFromCameraX = monsterLR[i].X - cameraPosition.X + screenOffSet;
		int monsterDistanceFromCameraY = monsterLR[i].Y - cameraPosition.Y + screenOffSet;

		if (monsterLR[i].X >= cameraPosition.X && monsterLR[i].X <= cameraPosition.X + cameraSize[0] && monsterLR[i].Y >= cameraPosition.Y && monsterLR[i].Y <= cameraPosition.Y + cameraSize[1]) {

			console.writeToBuffer(monsterDistanceFromCameraX, monsterDistanceFromCameraY, 234, 0x06);

		}

	}

}

//Render falling rocks. The shooters are now called rocks.
void renderShooter() {

	for (int i = 0; i < bullets.size(); ++i) {

		int bulletDistanceFromCameraX = bullets[i].X - cameraPosition.X + screenOffSet;
		int bulletDistanceFromCameraY = bullets[i].Y - cameraPosition.Y + screenOffSet;

		if (bullets[i].X >= cameraPosition.X && bullets[i].X <= cameraPosition.X + cameraSize[0] && bullets[i].Y >= cameraPosition.Y && bullets[i].Y <= cameraPosition.Y + cameraSize[1]) {
			console.writeToBuffer(bulletDistanceFromCameraX, bulletDistanceFromCameraY, 234, 0x06);
		}

	}

}