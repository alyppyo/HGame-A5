#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/**
 * Classe Element
 * 
 * Responsável pelos elementos gráficos que não se repetem horizontalmente ou verticalmente.
 * 
 */

class Element {
private:
	ALLEGRO_BITMAP * elementImage; // Imagem do elemento
	int x; // Posição atual do elemento no eixo X
	int y; // Posição atual do elemento no eixo Y
	int height; // Altura da imagem
	int width; // Largura da imagem
	int velocity; // Velocidade de deslocamento da imagem (definida pela camada na qual se encontra)
	bool flipHorizontal; // Caso seja verdadeiro, a imagem é desenhada espelhada horizontalmente
	float scale; // Escala a ser aplicada ao tamanho da imagem durante o desenho

public:
	Element(); // Construtor padrão
	Element(ALLEGRO_BITMAP *& parent, int x, int y, int newVelocity, bool flipHorizontal, float scale); // Construtor personalizado

	~Element(); // Destrutor

	void draw (); // Função de desenho do elemento
	void update (); // Função de update dos atributos do elemento com o tempo
	void setVelocity (int newVelocity); // Permite a alteração do atributo "velocity", que é privado
};

#endif
