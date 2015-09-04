#ifndef _SHOOTER_H
#define _SHOOTER_H
#include <vector>

using std::vector;

void spawnShooter(int X, int Y);
void bulletMovement();
void bulletUpdate();

struct Shooter {

	int X;
	int Y;
	int CoordX;
	int CoordY;
	int Direction;
	bool InRange;

};

#endif