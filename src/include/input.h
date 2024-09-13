#ifndef input_h
#define input_h
Uint32 mousestate;      // stores result of SDL_GetMouseState 
int mouseX; 
int mouseY; 
int firstclick;         // (camera.c) something about jitter

const Uint8 *keys;      // Array into result of SDL_GetKeyboardState

// enum mostly exists to specify pressed vs held lol
enum keystate {         
    NONE = 0,
    PRESSED = 1,        // if key pressed (first active frame)
    HELD = 2,           // if key held (active for >1 frame)
};

struct userinput {
    enum keystate UP;
    enum keystate DOWN;
    enum keystate LEFT;
    enum keystate RIGHT;
    enum keystate W;
    enum keystate A;
    enum keystate S;
    enum keystate D;
    enum keystate SHIFT;
} input;

void CheckInput();

#endif
