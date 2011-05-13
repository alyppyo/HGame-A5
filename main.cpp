#include <iostream>
#include<cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define FPS 15
#define WIDTH 800
#define HEIGHT 600

using namespace std;

struct Sprite {
	int x;
	int y;
	ALLEGRO_BITMAP * sprite;
};

class Animation {
	Sprite * animations;
	int spritesNumber;
	int currentSprite;
	
public:
	int x, y;

	Animation(ALLEGRO_BITMAP *& parent, int newSpritesNumber, int width, int height) {
		this->animations = new Sprite [newSpritesNumber];
		this->spritesNumber = newSpritesNumber;
		this->currentSprite = 0;
		this->x = 0;
		this->y = 0;
		
		int dx = 0;
		int dy = 0;

		for(int i = 0; i < newSpritesNumber; i++) {
			ALLEGRO_BITMAP * spriteTemp = al_create_sub_bitmap(parent, dx, dy, width, height);			
			
			this->animations[i].sprite = spriteTemp;
			this->animations[i].x = width;			
			this->animations[i].y = height;

			dx = dx + width;
		}
	}

	void draw() {
		al_clear_to_color(al_map_rgb_f(0, 0, 0));

		al_draw_bitmap(this->animations[currentSprite].sprite, this->x, this->y + this->animations[currentSprite].y, 0);
	}

	void update() {
		currentSprite++;
		if(currentSprite >= spritesNumber) currentSprite = 0;
		
		if(this->y + (animations[currentSprite].y*2) < HEIGHT) {
			this->y += 2;
			//this->y = min(HEIGHT,this->y + 2*animations[currentSprite].y);
		}
	}
};

//void loadContent();

int main()
{
	ALLEGRO_DISPLAY     * display    = NULL;
   ALLEGRO_EVENT_QUEUE * eventQueue = NULL;
   ALLEGRO_TIMER       * timer      = NULL;

   ALLEGRO_BITMAP      * helicopterSpriteSheet = NULL;	

	if(!al_init()) {
		cout << "Problemas na configuracao do Allegro. Abortando..." << endl;
		return 1;
	}

	al_init_image_addon();

  	timer = al_create_timer(1.0 / FPS);
   if(!timer) {
		cout << "failed to create timer!\n" << endl;
      return -1;
   }
 
   display = al_create_display(WIDTH, HEIGHT);
   if(!display) {
		cout << "failed to create display!\n" << endl;
      al_destroy_timer(timer);
      return -1;
   }

	eventQueue = al_create_event_queue();

	al_install_keyboard();
	if(!al_is_keyboard_installed()) {
		cout << "Problemas na deteccao do teclado. Abortando..." << endl;
	}

	al_register_event_source(eventQueue, al_get_display_event_source(display));
   al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());


	helicopterSpriteSheet = al_load_bitmap("img/sprite_helicopter.png");

	Animation * helicopter = new Animation(helicopterSpriteSheet, 3, 99, 41);	

	al_start_timer(timer);
	
	ALLEGRO_EVENT event;

	while (true) {
		if (al_event_queue_is_empty(eventQueue)) {
			helicopter->draw();
			al_flip_display();
		}

 		al_wait_for_event(eventQueue, &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
					return 0;
					break;
			case ALLEGRO_EVENT_KEY_CHAR:
					if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						return 0;
					else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
						helicopter->y -= 5;
					}						
					break;
			case ALLEGRO_EVENT_TIMER:
					helicopter->update();
					break;
		}
	}

	return 0;
}
/*
void loadContent()
{
	vector<BITMAP*> hImages;
	hImages.push_back(load_tga("img/helicoptero.tga",NULL));
	hImages.push_back(load_tga("img/helicoptero_2.tga",NULL));
	hImages.push_back(load_tga("img/helicoptero_3.tga",NULL));

	vector<int> hTime;
	hTime.push_back(5);
	hTime.push_back(5);
	hTime.push_back(5);

	//Animation helicopter(hImages,hTime,true,0,0);
}*/

