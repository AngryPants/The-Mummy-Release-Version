#include "loadlevel.h"
#include "game.h"
#include "boxes.h"
#include "Framework\console.h"
#include "monster.h"
#include "shooter.h"
#include "printMessages.h"
#include "camera.h"
#include "movecharacter.h"

//External Variables
extern Console console;
extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
extern vector<MonsterLR> monsterLR;
extern vector<MonsterUD> monsterUD;
extern vector<Boxes> boxes;
extern vector<Shooter> bullets;
extern string messageArray[messageArraySize];
extern COORD cameraPosition;
extern Mummy mummy;

//Local Variables
int monLRSpawnX2 = 0;
int monLRSpawnY2 = 0;
int monLRSpawnX1 = 0;
int monLRSpawnY1 = 0;
int monUDSpawnX = 0;
int monUDSpawnY = 0;
int bulletSpawnX = 0;
int bulletSpawnY = 0;

//These are to find out how long the map is, so that the camera knows to stop panning to the right when it reaches the end.
unsigned int g_longestX = 0;
unsigned int g_shortestX = worldSizeX;
unsigned int g_longestY = 0;
unsigned int g_shortestY = worldSizeY;

void updateWorldGrid(unsigned int levelNumber) {

	//Clear the vectors storing the monsters, bullets, etc from the previous level.
	monsterLR.clear();
	monsterUD.clear();
	boxes.clear();
	bullets.clear();

	mummy.isGrabbing = false;

	for (int t = 0; t < messageArraySize; ++t) {
		messageArray[t] = " ";
	}

	//Reset the value of the length of the level.
	g_longestX = 0;
	g_shortestX = worldSizeX;
	g_longestY = 0;
	g_shortestY = worldSizeY;

	//Resets the g_worldGrid array to '0' to be ready for repopulation.
	for (unsigned int x = 0; x < worldSizeX; ++x) {
		for (unsigned int y = 0; y < worldSizeY; ++y) {
			g_worldGrid[x][y] = '0';
		}
	}

	//The text file is read line by line. When a new line is read, the information is temporarily stored inside line.
	string line;
	
	/*fileNumberString is to store the level number, converted to a string,
	and itoa (levelNumber, fileNumberString, 10); converts the integer value of levelNumber into a string.
	This is actually pretty damned magical. All hail whoever invented this funciton.*/
	char fileNumberString[99];
	itoa (levelNumber, fileNumberString, 10);

	//Find the file to load.
	string fileName = "Levels/Level";
	fileName += fileNumberString;
	fileName += ".txt";
	ifstream levelFile(fileName);
	//This is to figure out which line in the text file we are at, which is also the same as the Y coordinates of the grid.
	int gridCoordsY = 0;

	if (levelFile.is_open()) {

		unsigned int spawnPointLR = 0;

		while(getline(levelFile, line)) {

			if (line.length() > g_longestX) {
				g_longestX = line.length();
			}

			++g_longestY;

			for (int gridCoordsX = 0; gridCoordsX < line.length(); ++gridCoordsX) {

				if (line[gridCoordsX] != ' ' && gridCoordsX < g_shortestX) {
					g_shortestX = gridCoordsX;
				}

				if (line[gridCoordsX] != ' ' && gridCoordsY < g_shortestY) {
					g_shortestY = gridCoordsY;
				}

				g_worldGrid[gridCoordsX][gridCoordsY] = line[gridCoordsX];

				//Spawning monsters that travel horizontally.
				if (line[gridCoordsX] == '$' && spawnPointLR == 0) {
					monLRSpawnX1 = gridCoordsX;
					monLRSpawnY1 = gridCoordsY;
					spawnPointLR = 1;
				}else if (line[gridCoordsX] == '$' && spawnPointLR == 1) {
					monLRSpawnX2 = gridCoordsX;
					monLRSpawnY2 = gridCoordsY;
					spawnPointLR = 0;
					spawnLeftRightMonster(monLRSpawnX1, monLRSpawnY1, monLRSpawnX2, monLRSpawnY2);			
				}

				//Spawning monsters that travel vertically
				if (line[gridCoordsX] == ',') {
					monUDSpawnX = gridCoordsX;
					monUDSpawnY = gridCoordsY;
					spawnUpDownMonster(monUDSpawnX, monUDSpawnY);
				}

				//Spawning the rocks that fall down on the player.
				if (line[gridCoordsX] == '.' ) {
					bulletSpawnX = gridCoordsX;
					bulletSpawnY = gridCoordsY;
					spawnShooter(bulletSpawnX, bulletSpawnY);
				}

				//Spawning Doors
				if (g_worldGrid[gridCoordsX][gridCoordsY] == '7' || g_worldGrid[gridCoordsX][gridCoordsY] == '8' || g_worldGrid[gridCoordsX][gridCoordsY] == '9') {
					g_worldGrid[gridCoordsX][gridCoordsY - 1] = '%';
					g_worldGrid[gridCoordsX][gridCoordsY - 2] = '%';
				}

				//Spawning Boxes
				if (g_worldGrid[gridCoordsX][gridCoordsY] == '+') {
					spawnBoxes(gridCoordsX, gridCoordsY, "Yellow");
				} else if (g_worldGrid[gridCoordsX][gridCoordsY] == '{') {
					spawnBoxes(gridCoordsX, gridCoordsY, "Purple");
				} else if (g_worldGrid[gridCoordsX][gridCoordsY] == '&') {
					spawnBoxes(gridCoordsX, gridCoordsY, "Grey");
				}

				//Setting player position to spawn point when new map loads.
				if (g_worldGrid[gridCoordsX][gridCoordsY] == '@') {
					charLocation.X = gridCoordsX;
					charLocation.Y = gridCoordsY;
				}

			}

			//Move on to the next line in the text file.
			++gridCoordsY;

		}

	}

	//Set Camera Position
	cameraPosition.X = 0;
	cameraPosition.Y = 0;

}