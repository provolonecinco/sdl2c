#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "input.h"
#include "gfx.h"

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

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, 640, 480);
			
    PrintHWInfo();
	VertexSpec();
	CreateGraphicsPipeline("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	SDL_Surface *icon = IMG_Load("icon.png");
	SDL_SetWindowIcon(window, icon);

	int run = 1;
	SDL_Event event;

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

		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(ShaderProgram);
		glUniform1f(0, g_uOffset);

		glBindVertexArray(VAObuf);
		glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(window);
        }
	}

	printf("Exiting...");
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}

