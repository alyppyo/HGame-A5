#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// Estrutura que guarda os elementos principais que definem o sprite.
// Atualmente só leva em consideração imagens animações compostas por imagens sequenciais lado a lado. Para ser mais completa
// deveria levar em consideração também a altura e largura do sprite dentro da imagem da animação.
struct Sprite {
	int x; // Posição X do sprite na imagem da animação
	int y; // Posição Y do sprite na imagem da animação
	ALLEGRO_BITMAP * sprite; // Ponteiro para a subimagem dentro da imagem da animação
};

//! A classe "Animation" está viciada para o uso do helicóptero. Para se usar outras animações, alguns atributos como o "up" não são necessários. Sendo assim, a dica é deixar essa classe como abstrata e fazer com que uma outra classe herde os atributos.
class Animation {
public:
	Sprite * animations;	// Vetor com os sprites que compõem a animação
	int spritesNumber; // Número de sprites que compõem a animação
	int currentSprite; // Sprite da animação que está ativo para desenho no momento
	
	int x, y; // Posição x e y da animação na tela
	double angle; // Ângulo de rotação da imagem ao ser desenhada (em radianos)
	int h, w; // Altura e largura da animação como aparecerá após desenhada
	bool up; // Atributo específico para o helicóptero. Se atualizada corretamente no main, informa se o jogador está solicitando que o helicóptero suba no momento.

	Animation(ALLEGRO_BITMAP *& parent, int newSpritesNumber); // Construtor padrão
	void draw(); // Função de desenho da animação
	void update(); // Função de update dos atributos da animação
};

#endif	
