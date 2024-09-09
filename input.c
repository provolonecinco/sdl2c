enum keystate {
	none = 0,
	pressed = 1, 
	held = 2,
};

struct userinput {
	enum keystate KEY_UP;
	enum keystate KEY_DOWN;
	enum keystate KEY_LEFT;
	enum keystate KEY_RIGHT;
};

void CheckInput(SDL_Event event) {	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_UP:
				if (!gUserInput.KEY_UP) {gUserInput.KEY_UP = pressed;} 
				else {gUserInput.KEY_UP = held;}
				break; 
			case SDLK_DOWN:
				if (!gUserInput.KEY_DOWN) {gUserInput.KEY_DOWN = pressed;} 
				else {gUserInput.KEY_DOWN = held;}
				break;
			case SDLK_LEFT:
				if (!gUserInput.KEY_LEFT) {gUserInput.KEY_LEFT = pressed;} 
				else {gUserInput.KEY_LEFT = held;}
				break; 
			case SDLK_RIGHT:
				if (!gUserInput.KEY_RIGHT) {gUserInput.KEY_RIGHT = pressed;} 
				else {gUserInput.KEY_RIGHT = held;}
				break; 
		}
	}

    // reset keystates on release
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: gUserInput.KEY_UP = none; break; 
			case SDLK_DOWN: gUserInput.KEY_DOWN = none; break; 
			case SDLK_LEFT: gUserInput.KEY_LEFT = none; break; 
			case SDLK_RIGHT:gUserInput.KEY_RIGHT = none; break; 
		}
	}
}
