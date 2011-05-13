#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(ALLEGRO_BITMAP * newBackground, Direction newDirection, int velocity) {
	this->background = newBackground;	
	this->direction = newDirection;
	this->velocity = velocity;	
}


