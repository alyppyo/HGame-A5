CC = g++
PARAMS = -Wall -pedantic -g
LIBS = -lm
LIBS_ALLEGRO_5 = `pkg-config --libs allegro_main-5.0 allegro_color-5.0 allegro_audio-5.0 allegro-5.0 allegro_memfile-5.0 allegro_ttf-5.0 allegro_image-5.0 allegro_font-5.0 allegro_primitives-5.0 allegro_acodec-5.0`
FONTE = $(wildcard *.cpp)
NAME = HGame

all:
	@$(CC) $(PARAMS) $(FONTE) -o $(NAME) $(LIBS) $(LIBS_ALLEGRO_5)
	@./$(NAME)


