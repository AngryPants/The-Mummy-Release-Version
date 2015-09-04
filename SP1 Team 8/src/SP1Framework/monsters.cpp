#include "monster.h"
#include "game.h"
#include "inventory.h"
#include "loadlevel.h"
#include "collisionDetection.h"

//External Variables
extern unsigned int g_levelNumber;
extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];

//Local Variables
int skip1=0;
int skip2=0;

enum {
	up,
	down,
	left,
	right
};

vector<MonsterLR> monsterLR;
vector<MonsterUD> monsterUD;

void monsterUpdate() {

	monsterLeftRightMovement();
	monsterUpDownMovement();
}

void spawnLeftRightMonster(int X, int Y, int XX, int YY) {

	MonsterLR newMonster;
	newMonster.X = X;
	newMonster.Y = Y;
	newMonster.CoordX = X;
	newMonster.CoordY = Y;
	newMonster.CoordXX = XX;
	newMonster.CoordYY = YY;
	newMonster.Direction = right;
	monsterLR.push_back(newMonster);

}

void spawnUpDownMonster(int X, int Y) {

	MonsterUD newMonster;
	newMonster.X = X;
	newMonster.Y = Y;
	newMonster.CoordX = X;
	newMonster.CoordY = Y;
	newMonster.Direction = down;
	monsterUD.push_back(newMonster);

}

void monsterLeftRightMovement() {

	for (unsigned int n=0; n<monsterLR.size(); n++)
	{
	
		if (monsterLR[n].Direction == right)
		{
			if(monsterLR[n].X == monsterLR[n].CoordXX || g_worldGrid[monsterLR[n].X+1][monsterLR[n].Y] == '1' || g_worldGrid[monsterLR[n].X+2][monsterLR[n].Y] == '%') {
				monsterLR[n].Direction = left;
			} else {
				++monsterLR[n].X;
			}
		} else if (monsterLR[n].Direction == left)
		{
			if(monsterLR[n].X == monsterLR[n].CoordX  ||  g_worldGrid[monsterLR[n].X-1][monsterLR[n].Y] == '1' || g_worldGrid[monsterLR[n].X-2][monsterLR[n].Y] == '%') {
				monsterLR[n].Direction = right;
			} else {
				--monsterLR[n].X;
			}
		}
			
		detectRestartLevel(monsterLR[n].X , monsterLR[n].Y);

		}

}

void monsterUpDownMovement() {

	if (skip2==2)
	{
		for (unsigned int n=0; n<monsterUD.size(); ++n)
		{
			if (monsterUD[n].Direction == down)
			{
				++monsterUD[n].Y;
				if(g_worldGrid[monsterUD[n].X][monsterUD[n].Y+1] == '1' || g_worldGrid[monsterUD[n].X][monsterUD[n].Y+1] == '%')
				monsterUD[n].Direction = up;
			} else if (monsterUD[n].Direction == up)
			{
				--monsterUD[n].Y;
				if(g_worldGrid[monsterUD[n].X][monsterUD[n].Y-1] == '1' || g_worldGrid[monsterUD[n].X][monsterUD[n].Y-1] == '%')
				monsterUD[n].Direction = down;
			}
			detectRestartLevel(monsterUD[n].X , monsterUD[n].Y);
		}
		skip2=0;
	} else skip2++;

}