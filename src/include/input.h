#ifndef input_h
#define input_h

enum keystate {
    NONE = 0,
    PRESSED = 1,
    HELD = 2,
};

struct userinput {
    enum keystate KEY_UP;
    enum keystate KEY_DOWN;
    enum keystate KEY_LEFT;
    enum keystate KEY_RIGHT;
} gUserInput;

void CheckInput(SDL_Event);

#endif
