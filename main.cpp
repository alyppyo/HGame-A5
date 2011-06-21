#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "ScrollingBackground.h"
#include "Animation.h"
#include "Element.h"

#define FPS_1L 30 // FPS da primeira camada
#define FPS_2L 20 // FPS da segunda camada
#define WIDTH 800 // Largura da tela
#define HEIGHT 600 // Altura da tela
#define MAX_ANGLE ALLEGRO_PI/8 // Ângulo máximo de rotação do helicóptero
#define NUM_ELEMENTS 30 // Número máximo de elementos gráficos que podem coexistir em uma mesma cena

using namespace std;

// Declaração dos ponteiros das imagens que serão utilizadas por todas as funções do programa
ALLEGRO_BITMAP * casa;
ALLEGRO_BITMAP * cacto;
ALLEGRO_BITMAP * cacto2;
ALLEGRO_BITMAP * nuvem;
ALLEGRO_BITMAP * nuvem2;

// Cria um elemento aleatório no céu
Element * randomElement () {
	int number = rand() % 2;
	ALLEGRO_BITMAP * imagem;

	// Escolhe aleatoriamente entre os dois tipos de nuvem existentes	
	switch(number) {
		case 0:
			imagem = nuvem;
			break;
		case 1:
			imagem = nuvem2;
			break;
	}

	// Escolhe aleatoriamente uma escala a ser apliacada na imagem 
	float scale = 0.6 + ((rand()%100)/100.f);

	return new Element(imagem, WIDTH, 20 + (rand()%250), 4, rand()%2, scale); // Cria um novo elemento com espelhamento randômico
}

// Essa função tem a mesma funcionalidade da função acima, mas para elementos que serão carregados no chão
Element * randomElementGround () {
	int number = rand() % 2;
	ALLEGRO_BITMAP * imagem;

	// Escolhe aleatoriamente entre os dois tipos de imagens de cacto existentes
	switch(number) {
		case 0:
			imagem = cacto;
			break;
		case 1:
			imagem = cacto2;
			break;
	}

	float scale = (30 + (rand()%20))/100.f;

	return new Element(imagem, WIDTH, 450 + (rand()%70), 3, rand()%2, scale);
}


// Função principal do jogo
//! Existem alguns trechos de código repetidos nesse arquivo. Uma otimização seria muito bem vinda. Além do mais, é necessário que todos os elementos do Allegro que foram criados sejam destruídos antes de finalizar a aplicação, e isso ainda não foi feito.
int main()
{
	// Declaração de elementos
	ALLEGRO_DISPLAY     * display    = NULL; // Tela 
   ALLEGRO_EVENT_QUEUE * eventQueue = NULL; // Fila de eventos

   ALLEGRO_TIMER       * timer1stLayer = NULL; // Timer da 1a camada
	ALLEGRO_TIMER       * timer2ndLayer = NULL; // Timer da 2a camada
	ALLEGRO_TIMER       * timerCreateElements = NULL; // Timer de criação de elementos no céu
	ALLEGRO_TIMER       * timerCreateElementsGround = NULL; // Times de criação de elementos no chão

   ALLEGRO_BITMAP      * helicopterSpriteSheet = NULL; // Imagem da animação do helicóptero
	ALLEGRO_BITMAP		  * imagePlanoDeFundo = NULL; // Imagem do plano de fundo
	ALLEGRO_BITMAP		  * montanhas = NULL; // Imagem das montanhas
	ALLEGRO_BITMAP		  * chao = NULL; // Imagem do chão

	int currentElement = 0; // Atual element
	int currentElementGround = 0;
	int randomNumber; // Número randômico

	srand(time(NULL));

	double gravidade = 1; // Velocidade de queda do helicóptero

	// Inicialização do Allegro
	if(!al_init()) {
		cout << "Problemas na configuracao do Allegro. Abortando..." << endl;
		return 1;
	}

	// Inicialização do addon de imagens
	al_init_image_addon();

	// Criação do timer da 1a camada
  	timer1stLayer = al_create_timer(1.0 / FPS_1L);
   if(!timer1stLayer) {
		cout << "failed to create timer!\n" << endl;
      return -1;
   }

	// Criação do timer da 2a camada
	timer2ndLayer = al_create_timer(1.0 / FPS_2L);
   if(!timer2ndLayer) {
		cout << "failed to create timer!\n" << endl;
      return -1;
   }

	// Criação do timer de criação de elementos no céu
	timerCreateElements = al_create_timer(2);
   if(!timerCreateElements) {
		cout << "failed to create timer!\n" << endl;
      return -1;
   }

	// Criação do timer de criação de elementos no chão
	timerCreateElementsGround = al_create_timer(1);
   if(!timerCreateElementsGround) {
		cout << "failed to create timer!\n" << endl;
      return -1;
   }
 
	// Criação da tela
   display = al_create_display(WIDTH, HEIGHT);
   if(!display) {
		cout << "failed to create display!\n" << endl;
      return -1;
   }

	// Criação da fila de eventos
	eventQueue = al_create_event_queue();

	// Instalação do teclado
	al_install_keyboard();
	if(!al_is_keyboard_installed()) {
		cout << "Problemas na deteccao do teclado. Abortando..." << endl;
	}

	// Registro de eventos na fila
	al_register_event_source(eventQueue, al_get_display_event_source(display)); // Eventos da tela
   al_register_event_source(eventQueue, al_get_timer_event_source(timer1stLayer)); // Eventos do timer da 1a camada
   al_register_event_source(eventQueue, al_get_timer_event_source(timer2ndLayer)); // Eventos do timer da 2a camada
   al_register_event_source(eventQueue, al_get_timer_event_source(timerCreateElements)); // Eventos do timer de criação de elementos
   al_register_event_source(eventQueue, al_get_timer_event_source(timerCreateElementsGround)); // Eventos do timer de criação de elementos no chão
	al_register_event_source(eventQueue, al_get_keyboard_event_source()); // Eventos de teclado

	// Carregar imagens
	helicopterSpriteSheet = al_load_bitmap("img/sprite_helicopter.png");
	imagePlanoDeFundo = al_load_bitmap("img/planoDeFundo.png");
	montanhas = al_load_bitmap("img/montanhas.png");
	chao = al_load_bitmap("img/chao.png");
	cacto = al_load_bitmap("img/cactus.png");
	cacto2 = al_load_bitmap("img/cactus_2.png");
	nuvem = al_load_bitmap("img/nuvem_01.png");
	nuvem2 = al_load_bitmap("img/nuvem_02.png");

	// Criação de Animações
	Animation * helicopter = new Animation(helicopterSpriteSheet, 3);	

	// Criação de planos de fundo com rolagem
	ScrollingBackground * bgPlanoDeFundo = new ScrollingBackground(imagePlanoDeFundo, 0, Horizontal, 1);
	ScrollingBackground * bgMontanhas = new ScrollingBackground(montanhas, -380, Horizontal, 2);
	ScrollingBackground * bgChao = new ScrollingBackground(chao, -500, Horizontal, 3);

	// Criação de elementos gráficos
	Element * objects[NUM_ELEMENTS];	// Objetos do céu
	Element * objectsGround[NUM_ELEMENTS]; // Objetos do chão

	// Inicia os ponteiros com NULL
	for(int i = 0; i < NUM_ELEMENTS; i++) {
		objects[i] = NULL;
		objectsGround[i] = NULL;
	}

	// Inicia os timers
	al_start_timer(timer1stLayer);
	al_start_timer(timer2ndLayer);
	al_start_timer(timerCreateElements);
	al_start_timer(timerCreateElementsGround);
	
	// Cria um evento para ser associado aos eventos da fila
	ALLEGRO_EVENT event;

	// Laço principal do jogo
	while (true) {
		// Quando não tiver mais nenhum evento para tratar, desenhe a tela
		if (al_event_queue_is_empty(eventQueue)) {
			// 1a camada
			bgPlanoDeFundo->draw();
			
			// 2a camada
			bgMontanhas->draw();
			bgChao->draw();

			// 3a camada
			for(int i = 0; i < NUM_ELEMENTS; i++) {
				if (objects[i] != NULL) objects[i]->draw();
				if (objectsGround[i] != NULL) objectsGround[i]->draw();
			}

			// 4a camada
			helicopter->draw();

			// Desenha a tela com todas as atualizações
			al_flip_display();
		}

		// Aguardar até que novos eventos aconteçam
 		al_wait_for_event(eventQueue, &event);

		// Decidir o que faze a partir do tipo do evento
		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE: // Caso tenha sido solicitado fechar a tela, encerrar o programa
					return 0;
					break;
			case ALLEGRO_EVENT_KEY_CHAR: // Caso um botão esteja sendo pressionado no teclado
					if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) // Caso seja o ESC, encerrar o programa
						return 0;
					else if (event.keyboard.keycode == ALLEGRO_KEY_UP) { // Caso seja a "seta pra cima", levantar e inclinar o helicóptero
						helicopter->y -= 5; // Subir a posição do helicóptero na tela
						  if(helicopter->y < 25) helicopter->y = 25; // Necessário para helicóptero não sumir da tela

						if(helicopter->angle > -MAX_ANGLE) { // Fazer o helicóptero dar uma guinada ao ser levantado
							helicopter->angle -= 0.1f;
						}

						helicopter->up = true; // Definir que a seta para cima está sendo pressionada (importante para atualização do ângulo)
						gravidade = 1; // Neutralizar a gravidade, visto que o helicóptero está subindo 
					}
					break;
			case ALLEGRO_EVENT_KEY_UP: // Caso uma tecla tenha sido liberada
					if (event.keyboard.keycode == ALLEGRO_KEY_UP) { // Se foi a seta pra cima
						helicopter->up = false; // Definir que a seta não está mais sendo pressionada (importante para a atualização do ângulo)
					}
					break;
			case ALLEGRO_EVENT_TIMER: // Caso um evento de timer tenha sido disparado
					if(event.timer.source == timer1stLayer) { // Caso seja o timer da 1a camada
						helicopter->update(); // Atualizar a posição do helicóptero
						for(int i = 0; i < NUM_ELEMENTS; i++) { // Atualizar as posições dos objetos do céu
							if (objects[i] != NULL) objects[i]->update();
						}

						if(!helicopter->up) { // Se a seta para cima estiver sendo pressionada
							if(helicopter->angle < 0) { // Realizar a guinada do helicóptero
								helicopter->angle += 0.1f;
							}

							helicopter->y += 2 + gravidade; // Fazer com que o helicóptero caia
							if (helicopter->y + helicopter->h > HEIGHT) helicopter->y = HEIGHT - helicopter->h; // Necessário para que o helicóptero não suma
							gravidade *= 1.05; // Atualizar exponencialmente o valor da gravidade
						}
					}
					else if(event.timer.source == timer2ndLayer) { // Caso seja o timer da 2a camada 
						bgPlanoDeFundo->update(); // Atualizar plano de fundo
						bgMontanhas->update(); // Atualizar montanhas
						bgChao->update(); // Atualizar o chão

						// Atualizar posição dos objetos no chão
						for(int i = 0; i < NUM_ELEMENTS; i++) {
							//if (objects[i] != NULL) objects[i]->update();
							if (objectsGround[i] != NULL) objectsGround[i]->update();
						}
					}
					else if(event.timer.source == timerCreateElements) { // Caso seja o timer de criação de elementos no céu
						randomNumber = rand() % (int)(NUM_ELEMENTS * 1.5); // Gerar um número rândomico

						if(randomNumber < NUM_ELEMENTS) { // Caso o número máximo de elementos não tenha sido atingido
							if(objects[currentElement] != NULL) delete objects[currentElement]; // Caso o elemento exista na posição atual, deletá-lo

							objects[currentElement] = randomElement(); // Criar novo elemento no céu

							currentElement++; // Atualizar para próxima posição do vetor de elementos do céu
							if(currentElement >= NUM_ELEMENTS) currentElement = 0; // Se o valor máximo tiver sido atingido, voltar para a primeira posição do vetor
						}
					}
					else if(event.timer.source == timerCreateElementsGround) { // Caso seja o timer de criação de elementos na terra
						// Realiza as mesmas funcionalidades que os elementos do céu, mas para o chão
						randomNumber = rand() % (int)(NUM_ELEMENTS * 1.5);

						if(randomNumber < NUM_ELEMENTS) {
							if(objectsGround[currentElementGround] != NULL) delete objectsGround[currentElementGround];

							objectsGround[currentElementGround] = randomElementGround();

							currentElementGround++;
							if(currentElementGround >= NUM_ELEMENTS) currentElementGround = 0;
						}
					}
					break;
			default: break;
		}
	}
	
	// Finaliza a aplicação
	return 0;
}

