#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad.h>
#include <cglm/cglm.h>

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

	if(!SDL_GL_CreateContext(window)) {
		printf("Cannot create OpenGL context: %s\n", SDL_GetError());
        exit(1);
    }
    
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
			printf("Cannot initialize GLAD");
			exit(1);
	} 
			
    PrintHWInfo();
	VertexSpec();
	CreateGraphicsPipeline();

	SDL_Surface *icon = IMG_Load("src/assets/icon.png");
	SDL_SetWindowIcon(window, icon);

	int run = 1;
	SDL_Event event;
	
	float dot1;
	vec3 A = {1.0, 2.0, 3.0};
	vec3 B = {1.5, 1.5, 1.5};
	dot1 = glm_vec3_dot(A, B);
	printf("Dot Product of A and B: %4.4f\n", dot1);

    // main loop
	while(run) {
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
                run = 0;
            }
			
            if(event.type == SDL_KEYDOWN | SDL_KEYUP) {
                CheckInput(event);
		    }
		
		if (gUserInput.KEY_UP) {
			g_uOffset += 0.01f;
			printf("g_uOffset: %2.2f\n", g_uOffset);
			}
		if (gUserInput.KEY_DOWN) {
			g_uOffset -= 0.01f;
			printf("g_uOffset: %2.2f\n", g_uOffset);
			}

        PreDraw();
		Draw();
        SDL_GL_SwapWindow(window);
        }
	}

	printf("Exiting...");
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}

