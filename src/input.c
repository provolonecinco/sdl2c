#include <SDL2/SDL.h>

#include "input.h"

void CheckInput(SDL_Event event) {	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_UP:
				if (!gUserInput.KEY_UP) {gUserInput.KEY_UP = PRESSED;} 
				else {gUserInput.KEY_UP = HELD;}
				break; 
			case SDLK_DOWN:
				if (!gUserInput.KEY_DOWN) {gUserInput.KEY_DOWN = PRESSED;} 
				else {gUserInput.KEY_DOWN = HELD;}
				break;
			case SDLK_LEFT:
				if (!gUserInput.KEY_LEFT) {gUserInput.KEY_LEFT = PRESSED;} 
				else {gUserInput.KEY_LEFT = HELD;}
				break; 
			case SDLK_RIGHT:
				if (!gUserInput.KEY_RIGHT) {gUserInput.KEY_RIGHT = PRESSED;} 
				else {gUserInput.KEY_RIGHT = HELD;}
				break; 
		}
	}

    // reset keystates on release
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: gUserInput.KEY_UP = NONE; break; 
			case SDLK_DOWN: gUserInput.KEY_DOWN = NONE; break; 
			case SDLK_LEFT: gUserInput.KEY_LEFT = NONE; break; 
			case SDLK_RIGHT:gUserInput.KEY_RIGHT = NONE; break; 
		}
	}
}
