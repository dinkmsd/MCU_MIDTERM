#include "input_reading.h"
#include "input_processing.h"
#include "stdio.h"
#include "global.h"
#include "software_timer.h"
#include "led7seg.h"
#include "output_display.h"
enum ButtonState{
	BUTTON_RELEASED,
	BUTTON_PRESSED,
	BUTTON_PRESSED_MORE_THAN_3S
};

enum ButtonState state = BUTTON_RELEASED;

int WhichButtonIsPressed() {
	if (is_button_pressed(0)) return INC_PRESSED;
	if (is_button_pressed(1)) return DEC_PRESSED;
	if (is_button_pressed(2)) return RESET_PRESSED;

	return 0; // None of these buttons are pressed
}

int WhichButtonIsPressed3s() {
	if (is_button_pressed_3s(0)) return INC_PRESSED_3S;
	if (is_button_pressed_3s(1)) return DEC_PRESSED_3S;

	return 0; // None of these buttons are pressed
}
void fsm_button_1s() {
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

void fsm_button_3s() {
	int button_pressed_3s = WhichButtonIsPressed3s();
	switch (button_pressed_3s) {
	case INC_PRESSED_3S:
		counter = (counter + 1) % 10;
		display7SEG(counter);
		break;
	case DEC_PRESSED_3S:
		counter = (counter - 1 + 10) % 10;
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
			fsm_button_1s();
		}
	case BUTTON_PRESSED:
		if (!WhichButtonIsPressed()) {
			state = BUTTON_RELEASED;
		} else {
			for (int i = 0; i < N0_OF_BUTTONS - 1; i++) {
				flagForFirstButtonIsReleased = 1;
				if (is_button_pressed_3s(i))
					state = BUTTON_PRESSED_MORE_THAN_3S;
			}
		}
	case BUTTON_PRESSED_MORE_THAN_3S:
		if (!WhichButtonIsPressed()) {
			state = BUTTON_RELEASED;
		}

		AllowToExecuteAfterASecondPressed = 1; // Allow the system to count for pressed button each half a second

		for (int i = 0; i < N0_OF_BUTTONS; i++) {
			if (pressed_a_second_while_holding(i)) {
				fsm_button_3s();
				flagForButtonPress1sWhileHolding[i] = 0;
				flagForFirstButtonIsReleased = 1;
			}
		}
		break;
	default:
		break;
	}
}


