#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include <iostream>

enum Direction {
	Horizontal,
	Vertical
}

class ScrollingBackground {
public:
	ScrollingBackground();
	ScrollingBackground(ALLEGRO_BITMAP * newBackground, Direction newDirection);
private:	
	int velocity;
	Direction direction;
	ALLEGRO_BITMAP * background;	
};

#endif

