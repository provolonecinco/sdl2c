#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad.h>

#include "input.h"
#include "opengl.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow(
		"SDL2 Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL);
	
	if (SDL_GL_CreateContext(window) == NULL) {
		printf("Cannot create OpenGL context: %s\n", SDL_GetError());
	} else {
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
			printf("Cannot initialize GLAD");
			exit(1);
		} else {
			PrintHWInfo();
			VertexSpec();
			CreateGraphicsPipeline();
		}
	}


	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 66, 104, 132, 255);

	SDL_Surface *icon = IMG_Load("src/assets/icon.png");
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
		PreDraw();
		Draw();
		SDL_GL_SwapWindow(window);	
	}

	printf("Goodbye!");
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
