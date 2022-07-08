

enum Color
{
    set_color,
    worm,
    rainbow
};


typedef struct
{
    uint8_t run_state;   //loop, start, done
    Color LED_mode;   //Rainbow, Set color
} LED_state;

