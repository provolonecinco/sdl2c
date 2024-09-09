#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// global user input
struct userinput gUserInput;

#include "input.c"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow(
		"SDL2 Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 66, 104, 132, 255);

	SDL_Surface *icon = IMG_Load("assets/icon.png");
	SDL_SetWindowIcon(window, icon);

	int quit = 0;
	SDL_Event event;

	// main loop
	while(!quit) {
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				quit = 1;
			}
			CheckInput(event);
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);	
	}

	printf("Goodbye!");
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
