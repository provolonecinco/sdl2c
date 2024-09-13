#ifndef input_h
#define input_h

const Uint8 *keys;

enum keystate {
    NONE = 0,
    PRESSED = 1,
    HELD = 2,
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
