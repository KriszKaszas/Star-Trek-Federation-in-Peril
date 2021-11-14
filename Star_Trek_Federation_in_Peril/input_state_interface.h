#ifndef INPUT_STATE_INTERFACE_H
#define INPUT_STATE_INTERFACE_H

#include <stdbool.h>

typedef struct input_state_interface{
    bool quit;
    bool left;
    bool right;
    bool up;
    bool down;
} InputStateInterface;

#endif // INPUT_STATE_INTERFACE_H
