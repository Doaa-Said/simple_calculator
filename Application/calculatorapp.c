/******************************************************************************
 *
 * File Name: calculatorapp.c
 *
 * Description: Source file for simple calculator
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "../HAL/lcd.h"          // Include the LCD library for display functions
#include "../HAL/keypad.h"       // Include the keypad library for input handling
#include "../MCAL/std_types.h"    // Include standard types for uint8, uint32, etc.
#include <util/delay.h>   // Include delay functions
int calculate(int first,int last,char op){
	int result=0;
	switch (op) {
					case '+':
						result =last+first;   // Addition
						break;
					case '-':
						result = first-last;   // Subtraction
						break;
					case '*':
						result = first* last;   // Multiplication
						break;
					case '/':
						result = first/last;   // Division
						break;
					}

return result;
}

int main(void) {
	LCD_init();          // Initialize the LCD display
	uint8 op_flag = 0;   // Flag to indicate if an operator has been selected
	uint8 input, op;    // Variables for input from keypad and selected operator
	uint32 last = 0, first = 0, result = 0; // Variables for operands and result

	for (;;) {           // Infinite loop for continuous operation

			input = KEYPAD_getPressedKey();  // Retrieve the key pressed on the keypad

			// Check if the pressed key corresponds to a digit (0-9)
			if (input >= 0 && input <= 9) {
				// If no operator has been selected yet, update the first operand
				if (!op_flag) {
					first = input + first * 10;  // Construct the first number by shifting and adding
					LCD_intgerToString(input);   // Display the current digit on the LCD
				} else {
					// If an operator has already been selected, update the second operand
					last = input + last * 10;     // Construct the second number by shifting and adding
					LCD_intgerToString(input);   // Display the current digit on the LCD
				}

			} else {
				// Check if the input corresponds to the equals key
				if (input == '=') {
					LCD_displayCharacter(input); // Display the equals sign on the LCD
					LCD_displayStringRowColumn(1, 0, "Ans="); // Display the "Ans=" label on the second row
					// Perform the calculation based on the selected operator
					result = calculate(result, last, op);
					LCD_intgerToString(result); // Display the calculated result on the LCD

				} else if (input == 13) { // Check if the input is for clearing/resetting the calculator
					LCD_clearScreen();     // Clear the LCD display to prepare for new input
					last = 0;              // Reset the last operand to zero
					first = 0;             // Reset the first operand to zero
					op_flag = 0;           // Reset the operator flag to indicate no operator is selected
				} else {
					// If an operator was previously selected, calculate the current result
					if (op_flag) {
						result = calculate(result, last, op);
						last = 0; // Reset the last operand for the next input
					} else {
						result = first; // If no operator was selected, the result is the first operand
						op_flag = 1; // Set the flag to indicate an operator has now been selected
					}
					op = input;            // Store the newly selected operator
					LCD_displayCharacter(op); // Display the operator on the LCD
				}
			}
			_delay_ms(500);           // Introduce a delay to debounce button presses
		}
	}




		}
		_delay_ms(500);           // Delay to prevent button bouncing
	}
}
