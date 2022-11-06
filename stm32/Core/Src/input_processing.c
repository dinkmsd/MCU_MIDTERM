/*
 * input_processing.c
 *
 *  Created on: Oct 24, 2022
 *      Author: TIEN
 */
#include "input_reading.h"
#include "input_processing.h"
#include "stdio.h"
#include "global.h"
#include "software_timer.h"
#include "led7seg.h"
#include "output_display.h"
enum ButtonState{
	BUTTON_RELEASED,
	BUTTON_PRESSED
};

enum ButtonState state = BUTTON_RELEASED;

int WhichButtonIsPressed() {
	if (is_button_pressed(0)) return INC_PRESSED;
	if (is_button_pressed(1)) return DEC_PRESSED;
	if (is_button_pressed(2)) return RESET_PRESSED;

	return 0; // None of these buttons are pressed
}

void fsm_button() {
	int button_pressed = WhichButtonIsPressed();
	switch (button_pressed) {
	case INC_PRESSED:
		counter = (counter + 1) % 10;
		display7SEG(counter);
		break;
	case DEC_PRESSED:
		counter = (counter - 1 + 10) % 10;
		display7SEG(counter);
		break;
	case RESET_PRESSED:
		counter = 0;
		display7SEG(counter);
		break;
	default:
		break;
	}
}

void fsm_simple_button_run() {
	switch (state) {
	case BUTTON_RELEASED:
		if (WhichButtonIsPressed()) {
			state = BUTTON_PRESSED;
			fsm_button();
		}
	case BUTTON_PRESSED:
		if (!WhichButtonIsPressed()) {
			state = BUTTON_RELEASED;
		}
	default:
		break;
	}
}


