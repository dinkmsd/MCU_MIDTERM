#ifndef INC_LED7SEG_H_
#define INC_LED7SEG_H_

#define ON_7SEG			SET
#define OFF_7SEG		RESET
#define NUMBERS_LED7	4
#include "main.h"

void update_buffer();
void led7SEG_init(void);
void led_init(void);
void display7SEG(int number);
void update7SEG(int index);
void led_clear(void);
void displayMode();
void displayREDTIME();

#endif /* INC_LED7SEG_H_ */
