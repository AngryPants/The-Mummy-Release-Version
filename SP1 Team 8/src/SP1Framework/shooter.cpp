#include "shooter.h"
#include "game.h"
#include "inventory.h"
#include "loadlevel.h"
#include "collisionDetection.h"

extern unsigned int g_levelNumber;
extern COORD charLocation;
extern unsigned int g_worldGrid[worldSizeX][worldSizeY];
int skip=0;

enum {
	nopes,
	ups,
	downs,
	lefts,
	rights
};

//The bullets are now the falling rocks.
vector<Shooter> bullets;

void bulletUpdate() {

	bulletMovement();

}

void spawnShooter(int X, int Y) {

	Shooter newBullet;
	newBullet.X = X;
	newBullet.Y = Y;
	newBullet.CoordX = X;
	newBullet.CoordY = Y;
	newBullet.Direction = nopes;
	newBullet.InRange = false;
	bullets.push_back(newBullet);
	

}

void bulletMovement()
{
	for (int n=0; n<bullets.size(); ++n)
	{
		if((charLocation.X <= (bullets[n].CoordX+10)) && (charLocation.X >= (bullets[n].CoordX-10)) && (charLocation.Y <= (bullets[n].CoordY+10)) && ( charLocation.Y >= (bullets[n].CoordY-10)))
		{
			bullets[n].InRange = true;
		}
		if (bullets[n].InRange==true && bullets[n].Direction == nopes)
		{
			// 8 sides
			if(charLocation.X == bullets[n].CoordX && charLocation.Y < bullets[n].CoordY)	// top 
			{
				bullets[n].Direction = ups;
			}
			else if(charLocation.X > bullets[n].CoordX && charLocation.Y == bullets[n].CoordY)	// right 
			{
				bullets[n].Direction = rights;
			}
			else if(charLocation.X == bullets[n].CoordX && charLocation.Y > bullets[n].CoordY)	// bottom 
			{
				bullets[n].Direction = downs;
			}
			else if(charLocation.X < bullets[n].CoordX && charLocation.Y == bullets[n].CoordY)	// left
			{
				bullets[n].Direction = lefts;
			}
		}
		if (skip==4)
		{
			if(bullets[n].Direction == ups)	// top 
			{
				bullets[n].Y--;
			}
			else if(bullets[n].Direction == rights)	// rights
			{
				bullets[n].X++;
			}
			else if(bullets[n].Direction == downs)	// bottom 
			{
				bullets[n].Y++;
			}
			else if(bullets[n].Direction == lefts)	// lefts
			{
				bullets[n].X--;
			}
			skip=0;
		}
		else skip++;

		if (g_worldGrid[bullets[n].X][bullets[n].Y] == '1' || g_worldGrid[bullets[n].X][bullets[n].Y] == '%')
		{
			bullets[n].X = bullets[n].CoordX;
			bullets[n].Y = bullets[n].CoordY;
			bullets[n].Direction=nopes;
			bullets[n].InRange =false;
		}


		detectRestartLevel(bullets[n].X , bullets[n].Y);
	}
}