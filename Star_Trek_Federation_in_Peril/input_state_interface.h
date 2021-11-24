#ifndef INPUT_STATE_INTERFACE_H_INCLUDED
#define INPUT_STATE_INTERFACE_H_INCLUDED

#include <stdbool.h>

typedef struct inputstateinterface{
    bool quit;
    bool up;
    bool down;
    bool left;
    bool right;
} InputStateInterface;

#endif // INPUT_STATE_INTERFACE_H_INCLUDED
