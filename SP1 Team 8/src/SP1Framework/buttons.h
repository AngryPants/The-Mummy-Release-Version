#ifndef _BUTTONS_H
#define _BUTTONS_H

void detectButtonActivated(unsigned int buttonCoordsX, unsigned int buttonCoordsY, unsigned int wallCoordsX1, unsigned int wallCoordsY1, unsigned int wallCoordsX2, unsigned int wallCoordsY2, unsigned int wallCoordsX3, unsigned int wallCoordsY3);
bool checkForPlayer(unsigned int buttonCoordsX, unsigned int buttonCoordsY);

#endif