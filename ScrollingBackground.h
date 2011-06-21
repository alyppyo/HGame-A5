#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// Enumeração com a definição dos tipos de movimento possíveis para o plano de fundo
enum Direction {
	Horizontal,
	Vertical
};

// Classe responsável por criar o efeito de continuidade do plano de fundo durante o movimento.
class ScrollingBackground {
public:
	ScrollingBackground(); // Construtor padrão
	ScrollingBackground(ALLEGRO_BITMAP * newBackground, int y, Direction newDirection, int newVelocity); // Construtor personalizado
	void draw (void); // Método de desenho da classe
	void update (void); // Método de atualização dos parâmetros do plano de fundo animado
	void setVelocity(int newVelocity); // Define a velocidade de rolagem do plano de fundo (definido pela camada)

private:	
	int velocity; // Velocidade de rolagem do plano de fundo
	int x; // Posição X no qual a imagem será desenhada
	int y; // Posição Y na qual a imagem será desenhada
	Direction direction; // Direção de rolagem do plano de fundo
	ALLEGRO_BITMAP * background; // Imagem do plano de fundo que será rolada indefinidamente
};

#endif

