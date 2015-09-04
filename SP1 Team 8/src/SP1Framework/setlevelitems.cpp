#include "game.h"
#include "teleporters.h"
#include "buttons.h"

extern unsigned int g_levelNumber;

void setItemsInLevel() {

	if (g_levelNumber == 0) {
		detectUseTeleporters(143, 8, 143, 24);
	}

	if (g_levelNumber == 1) {
		detectButtonActivated(35, 18, 24, 18, 24, 17, 24, 16);
	}

	if (g_levelNumber == 2) {

		detectUseTeleporters(86, 24, 76, 30);
		detectButtonActivated(41, 9, 50, 24, 50, 23, 50, 22);
		detectButtonActivated(78, 16, 106, 20, 106, 19, 106, 18);
		detectUseTeleporters(47, 24, 90, 24);
		detectUseTeleporters(53, 6, 139, 13);
		detectButtonActivated(73, 4, 80, 6, 80, 5, 80, 4);

	}
	if (g_levelNumber == 3) {

		detectUseTeleporters(109, 3, 139, 7);	// p1
		detectUseTeleporters(96, 3, 118, 7);	// p2
		detectUseTeleporters(75, 3, 63, 11);	// p3
		detectUseTeleporters(70, 3, 85, 3);		// p4
		detectUseTeleporters(37, 3, 68, 11);	// p5
		detectButtonActivated(3, 3, 42, 4, 41, 4, 43, 4);		// b1
		detectButtonActivated(3, 7, 42, 8, 41, 8, 43, 8);		// b2
		detectButtonActivated(3, 11, 73, 10, 73, 9, 73, 11);	// b3


	}
	if (g_levelNumber == 4) {

		detectButtonActivated(139, 19, 100, 12, 101, 12, 99, 12);	// b1
		detectButtonActivated(90, 3, 38, 10, 38, 11, 38, 9);		// b2
		detectButtonActivated(3, 11, 87, 12, 88, 12, 86, 12);		// b3

	}

	if (g_levelNumber == 5) {

		detectUseTeleporters(23, 51, 48, 47);	// p1 A
		detectUseTeleporters(43, 51, 28, 43);	// p2 A
		detectUseTeleporters(23, 47, 48, 39);	// p3 C
		detectUseTeleporters(53, 43, 28, 35);	// p4 A
		detectUseTeleporters(23, 39, 48, 31);	// p5 B
		detectUseTeleporters(48, 35, 28, 27);	// p6 C
		detectUseTeleporters(33, 31, 48, 23);	// p7 B
		detectUseTeleporters(48, 27, 28, 19);	// p8 B
		detectUseTeleporters(28, 23, 48, 15);	// p9 C
		detectUseTeleporters(53, 19, 28, 11);	// p10 A
		detectUseTeleporters(23, 15, 48, 7);	// p11 A
		detectUseTeleporters(43, 11, 28, 3);	// p12 C
		detectUseTeleporters(33, 7, 53, 3);		// p13 

		detectUseTeleporters(48, 51, 38, 3);	// p1 B
		detectUseTeleporters(53, 51, 38, 3);	// p1 C

		detectUseTeleporters(28, 47, 38, 3);		// p2 B
		detectUseTeleporters(33, 47, 38, 3);	// p2 C

		detectUseTeleporters(43, 43, 38, 3);	// p3 A
		detectUseTeleporters(48, 43, 38, 3);	// p3 B

		detectUseTeleporters(28, 39, 38, 3);		// p4 B
		detectUseTeleporters(33, 39, 38, 3);	// p4 C

		detectUseTeleporters(43, 35, 38, 3);	// p5 A
		detectUseTeleporters(53, 35, 38, 3);	// p5 C

		detectUseTeleporters(23, 31, 38, 3);		// p6 A
		detectUseTeleporters(28, 31, 38, 3);		// p6 B

		detectUseTeleporters(43, 27, 38, 3);	// p7 A
		detectUseTeleporters(53, 27, 38, 3);	// p7 C

		detectUseTeleporters(23, 23, 38, 3);		// p8 A
		detectUseTeleporters(33, 23, 38, 3);	// p8 C

		detectUseTeleporters(43, 19, 38, 3);	// p9 A
		detectUseTeleporters(48, 19, 38, 3);	// p9 B

		detectUseTeleporters(28, 15, 38, 3);		// p10 B
		detectUseTeleporters(33, 15, 38, 3);	// p10 C

		detectUseTeleporters(48, 11, 38, 3);	// p11 B
		detectUseTeleporters(53, 11, 38, 3);	// p11 C

		detectUseTeleporters(23, 7, 38, 3);		// p12 A
		detectUseTeleporters(28, 7, 38, 3);		// p12 B

	}

	if (g_levelNumber == 6) {

		detectUseTeleporters(41, 46, 2, 6);		// p1
		detectUseTeleporters(55, 46, 70, 39);	// p2
		detectUseTeleporters(86, 46, 2, 46);	// p3
		detectUseTeleporters(102, 46, 121, 46);	// p4
		detectUseTeleporters(38, 37, 41, 6);	// p5
		detectUseTeleporters(121, 33, 36, 14);	// p6
		detectUseTeleporters(98, 29, 102, 6);	// p7
		detectUseTeleporters(96, 34, 121, 6);	// p8
	}

	
if (g_levelNumber == 7) {

		detectUseTeleporters(65, 21, 3, 25);		// p1
		detectUseTeleporters(110, 21, 174, 25);	// p2
		detectUseTeleporters(110, 17, 94, 12);	// p3
		detectUseTeleporters(65, 17, 102, 11);	// p4
		
	}

if (g_levelNumber == 8) {

		detectUseTeleporters(192, 84, 194, 7);
}


}