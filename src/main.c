#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/struct.h>
#include "stb_image.h"

#include "input.h"
#include "gfx.h"

// globals (check gfx.h)
const int screenWidth   = 640;
const int screenHeight  = 480;

int main(int argc, char* argv[]) {
	// Initialize SDL and create window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow(
		"SDL2 Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
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
	glViewport(0, 0, screenWidth, screenHeight);
    
    // Populate buffer objects, load shaders from file
	LoadBuffers();
	LoadShaders("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	// Load texture from image file
	int widthImg, heightImg, numColCh = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("nelson.png", &widthImg, &heightImg, &numColCh, 0);

    // Create texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture); 

    // Specify texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Create shader program to pass texture into
    glUseProgram(ShaderProgram);
	GLuint tex0Uni = glGetUniformLocation(ShaderProgram, "tex0");

    // Create camera and specify location
	vec3s campos = {0.0f, 0.5f, 2.0f};
	InitCamera(screenWidth, screenHeight, campos);

    // Last few variables
	keys = SDL_GetKeyboardState(NULL);
	run = 1;
	SDL_Event event;

    // main loop
	while(run) {
        // Process SDL Events first
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				run = 0;
			}
		}

		CheckInput();

        // Set BG color, reset some bits etc
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glUseProgram(ShaderProgram);

        // Process camera logic and send to shader
		CameraInputs(window);
		CameraMatrix(45.0f, 0.1f, 100.0f, ShaderProgram, "camMatrix");

        // Specify textures (again)
		glUniform1i(tex0Uni, 0);
		glBindTexture(GL_TEXTURE_2D, texture);

        // Send buffers to be rendered
		glBindVertexArray(VAObuf);
		glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);
        
		SDL_Delay(16);  // cap to like 60fps (this is bad code)
	}

    // If run = 0, quit
	printf("Exiting...");
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}

		
