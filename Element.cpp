#include "Element.h"

// Construtor padrão
Element::Element() {}

// Construtor personalizado
Element::Element(ALLEGRO_BITMAP *& parent, int x, int y, int newVelocity, bool flipHorizontal, float scale) {
	this->elementImage = parent;
	this->x = x;
	this->y = y;
	this->velocity = newVelocity;
	this->flipHorizontal = flipHorizontal;
	this->scale = scale;
}

// Destrutor
Element::~Element() {}

// Desenha o elemento na tela utilizando os atributos pré-definidos
void Element::draw() {
	// Decidir o tipo de espelhamento utilizado no desenho da imagem
	int flipType = (this->flipHorizontal) ? ALLEGRO_FLIP_HORIZONTAL : 0;

	// Desenha o elemento na posição selecionada, escalonado e espelhado (de acordo com os atributos definidos na classe.
	al_draw_scaled_bitmap(this->elementImage, 0, 0,
										al_get_bitmap_width(this->elementImage), al_get_bitmap_height(this->elementImage),
										x, y,
										al_get_bitmap_width(this->elementImage) * this->scale, al_get_bitmap_height(this->elementImage) * this->scale, flipType);
}

// Update de velocidade
// Neste caso, o eixo levado em consideração é o x (horizontal), visto que os elementos correm no mesmo sentido que o plano de fundo,ou seja, da direita para a esquerda
void Element::update() {
	this->x -= velocity;
}

// Definição de velocidade
// Atualiza o valor da velocidade
void Element::setVelocity(int newVelocity) {
	this->velocity = newVelocity;
}

