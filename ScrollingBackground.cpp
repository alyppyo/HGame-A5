#include "ScrollingBackground.h"

// Construtor padrão
ScrollingBackground::ScrollingBackground(ALLEGRO_BITMAP * newBackground, int y, Direction newDirection, int newVelocity) {
	this->background = newBackground;	
	this->direction = newDirection;
	this->velocity = newVelocity;	
	this->x = 0;
	this->y = y;
}

// Função de desenho do plano de fundo
//! Essa função está definida para o tamanho da aplicação (800x600). Seria interessante que ela fosse substituída por uma onde esses parâmetros fossem consultados a partir da classe, para não deixá-la estática como está.
void ScrollingBackground::draw ( void ) {
	if( al_get_bitmap_width(this->background)-this->x < 800 ) {
		al_draw_scaled_bitmap(this->background, this->x, this->y,
										al_get_bitmap_width(this->background) - this->x, 600,
										0, 0,
										al_get_bitmap_width(this->background) - this->x, 600, 0);
		al_draw_scaled_bitmap(this->background,
				0,
				this->y,
				800 - (al_get_bitmap_width(this->background) - this->x),
				600,
				(al_get_bitmap_width(this->background) - this->x),
				0,
				800 - (al_get_bitmap_width(this->background) - this->x),
				600, 0);
	}
	else
		al_draw_scaled_bitmap(this->background, this->x, this->y, 800, 600, 0, 0, 800, 600, 0);
}

// Realiza a atualização da posição no eixo horizontal, passando a ilusão de rolagem do plano de fundo
void ScrollingBackground::update( void ) {
	if(this->direction == Horizontal) {
		this->x = (this->x + this->velocity) % al_get_bitmap_width(this->background);
	}
	else {
		this->y = (this->y + this->velocity) % al_get_bitmap_height(this->background);
	}
}

// Define a velocidade de rolagem do plano de fundo (geralmente definido pela camada)
void ScrollingBackground::setVelocity(int newVelocity) {
	this->velocity = newVelocity;
}

