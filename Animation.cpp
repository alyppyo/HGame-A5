#include "Animation.h"

// Classe de desenho da animação
Animation::Animation (ALLEGRO_BITMAP *& parent, int newSpritesNumber) {
	this->animations = new Sprite [newSpritesNumber];
	this->spritesNumber = newSpritesNumber;
	this->currentSprite = 0;
	this->x = 100;
	this->y = 100;
	this->angle = 0;
	this->h = al_get_bitmap_height(parent);
	this->w = al_get_bitmap_width(parent) / newSpritesNumber;
	this->up = false;
	
	int dx = 0;
	int dy = 0;

	// Laço responsável por criar as subimagens (sprites) a partir de uma imagem que contém toda a animação (spritesheet).
	for(int i = 0; i < newSpritesNumber; i++) {
		ALLEGRO_BITMAP * spriteTemp = al_create_sub_bitmap(parent, dx, dy, this->w, this->h); // Cria a subimagem como um pedaço da imagem da animação.			
		
      // Define os parâmetros da subimagem
		this->animations[i].sprite = spriteTemp;
		this->animations[i].x = this->w;			
		this->animations[i].y = this->h;

		dx = dx + this->w; // Atualiza a posição de leitura para o próximo pedaço da imagem da animação.
		//! ATENÇÃO: a linha acima leva apenas em consideração imagens que possua uma animação onde os quadros estão dispostos horizontalmente quadro a quadro. Para que seja realmente efetiva, deveria se pegar qualquer posição da imagem. Essa é um trecho de código que precisa ser melhorado no futuro.
	}
}

// Desenha a imagem que esteja ativa no momento da animação
void Animation::draw() {
	al_draw_rotated_bitmap(this->animations[currentSprite].sprite, (this->w / 4), 0,
                          this->x, this->y, angle, 0);
}

// Atualiza a subimagem do momento para a próxima subimagem da animação a ser desenhada
void Animation::update() {
	//currentSprite++;
	//if(currentSprite >= spritesNumber) currentSprite = 0;
	currentSprite = (currentSprite+1) % spritesNumber;
}

