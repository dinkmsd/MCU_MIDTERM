#include "main.h"
#include "input_processing.h"
#include "input_reading.h"
#include "global.h"

#define DURATION_3S 					300
#define	DURATION_1S						100

#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_TypeDef *buttonPort[N0_OF_BUTTONS] = {
		INC_GPIO_Port,
		DEC_GPIO_Port,
		RESET_GPIO_Port
};

static uint16_t buttonPin[N0_OF_BUTTONS] = {
		INC_Pin,
		DEC_Pin,
		RESET_Pin
};

static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

static uint8_t flagButton3s[N0_OF_BUTTONS];

static uint16_t counterButton3s[N0_OF_BUTTONS];
static uint16_t counterButton1s[N0_OF_BUTTONS];

void button_reading(void) {
	for (int i = 0; i < N0_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
			buttonBuffer[i] = debounceButtonBuffer1[i];
			if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
				if (flagButton3s[i] == 1) {
					if (counterButton1s[i] < DURATION_1S){
						counterButton1s[i]++;
					} else {
						counterButton1s[i] = 0;
						flagButton1s[i] = 1;
					}
				} else {
					counterButton1s[i] = 0;
					flagButton1s[i] = 0;
				}
				if(counterButton3s[i] < DURATION_3S) {
					counterButton3s[i]++;
				} else {
					flagButton3s[i] = 1;
				}
			} else {
				counterButton3s[i] = 0;
				counterButton1s[i] = 0;
				flagButton3s[i] = 0;
				flagButton1s[i] = 0;
			}
		}
	}
}
// Check if a button is pressed or not
unsigned char is_button_pressed(uint8_t index) {
	if (index >= N0_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

// Check for button is pressed more than a second or not
unsigned char is_button_pressed_3s (unsigned char index ) {
	if(index >= N0_OF_BUTTONS ) return 0xff ;
	return (flagButton3s[index] == 1) ;
}

unsigned char is_button_pressed_1s_while_holding(unsigned char index) {
	if(index >= N0_OF_BUTTONS) return 0xff ;
	return (flagButton1s[index] == 1) ;
}
