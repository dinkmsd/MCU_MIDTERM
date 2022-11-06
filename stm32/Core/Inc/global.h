
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

// declare the duration of all default leds 

#define INC_PRESSED							10
#define DEC_PRESSED							11
#define RESET_PRESSED						12

#define INC_PRESSED_3S						14
#define DEC_PRESSED_3S						15
#define RESET_PRESSED_3S					16


#define DURATION_FOR_AUTO_DECREASING		10000
#define DURATION_1S							1000
#define DURATION_HALF_OF_SECOND				500

extern int counter;
extern int flagForFirstButtonIsReleased;
extern int flagForButtonPress1sWhileHolding[3];
extern int AllowToExecuteAfterASecondPressed;
#endif /* INC_GLOBAL_H_ */
