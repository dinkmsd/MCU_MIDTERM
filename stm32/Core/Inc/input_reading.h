#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include "main.h"

#define N0_OF_BUTTONS 3

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_3s(unsigned char index);
unsigned char is_button_pressed_1s_while_holding(unsigned char index);
#endif /* INC_INPUT_READING_H_ */



















