#ifndef _MONSTER_H
#define _MONSTER_H
#include <vector>

using std::vector;

void spawnLeftRightMonster(int X, int Y, int XX, int YY);
void spawnUpDownMonster(int X, int Y);
void monsterLeftRightMovement();
void monsterUpDownMovement();
void monsterUpdate();

struct MonsterLR {

	int X;
	int Y;
	int CoordX;
	int CoordY;
	int CoordXX;
	int CoordYY;
	int Direction;

};

struct MonsterUD {

	int X;
	int Y;
	int CoordX;
	int CoordY;
	int CoordXX;
	int CoordYY;
	int Direction;

};

#endif