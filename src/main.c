#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "input.h"
#include "gfx.h"
#include "shader.h"

int main(int argc, char* argv[]) {
	// Initialize SDL and create window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow(
		"SDL2 Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL);
	
	// Set window icon
	SDL_Surface *icon = IMG_Load("icon.png");
	SDL_SetWindowIcon(window, icon);

	// Create OpenGL Context
	SDL_GL_CreateContext(window);

    // Initialize GLAD
	gladLoadGL();	

	// Print hardware info		
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, 640, 480);

	LoadBuffers();
	LoadShaders("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(ShaderProgram, "scale");

	int run = 1;
	GLfloat rotation = 0;
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

			if (gUserInput.KEY_UP) {scale += 0.01f;}
			if (gUserInput.KEY_DOWN) {scale -= 0.01f;}

			glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glUseProgram(ShaderProgram);

			// Create identity matrices
			mat4 model;
			glm_mat4_identity(model);
			mat4 view;
			glm_mat4_identity(view);
			mat4 projection;
			glm_mat4_identity(projection);

			if (gUserInput.KEY_LEFT) {rotation += 0.1f;}
			if (gUserInput.KEY_RIGHT) {rotation -= 0.1f;}

			vec3 displacement = {0.0f, -1.0f, -3.0f};
			vec3 rotaxis = {0.0f, -1.0f, 0.0f};
			glm_rotate(model, rotation, rotaxis);
			glm_translate(view, displacement);
			glm_perspective(45.0f, (float)(640/480), 0.1f, 100.0f, projection);
			
			// Pass matrices into shaders
			int modelLoc = glGetUniformLocation(ShaderProgram, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (void*)model);
			int viewLoc = glGetUniformLocation(ShaderProgram, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (void*)view);
			int projectionLoc = glGetUniformLocation(ShaderProgram, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (void*)projection);


			glUniform1f(uniID, 0.5f + scale);

			glBindVertexArray(VAObuf);
			glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
			glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
			SDL_GL_SwapWindow(window);
		}
}

	printf("Exiting...");
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
		