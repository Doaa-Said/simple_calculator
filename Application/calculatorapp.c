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

int main(void) {
	LCD_init();          // Initialize the LCD display
	uint8 op_flag = 0;   // Flag to indicate if an operator has been selected
	uint8 input, op;    // Variables for input from keypad and selected operator
	uint32 last = 0, first = 0, result = 0; // Variables for operands and result

	for (;;) {           // Infinite loop for continuous operation

		input = KEYPAD_getPressedKey();  // Get the pressed key from the keypad

		// Check if the input is a digit (0-9)
		if (input >= 0 && input <= 9) {
			// If no operator has been selected, update the first operand
			if (!op_flag) {
				first = input + first * 10;  // Construct the first number
				LCD_intgerToString(input);   // Display the current digit on LCD
			} else {
				// If an operator has been selected, update the second operand
				last = input + last * 10;     // Construct the last number
				LCD_intgerToString(input);   // Display the current digit on LCD
			}

		} else {
			// Check if the input is the equals key
			if (input == '=') {
				LCD_displayCharacter(input); // Display the equals sign
				LCD_displayStringRowColumn(1, 0, "Ans="); // Display answer label
				// Perform calculation based on the operator
				switch (op) {
				case '+':
					result = first + last;   // Addition
					break;
				case '-':
					result = first - last;   // Subtraction
					break;
				case '*':
					result = first * last;   // Multiplication
					break;
				case '/':
					result = first / last;   // Division
					break;
				}
				LCD_intgerToString(result); // Display the result on LCD

			} else if (input == 13) { // Check if the input is for clear/reset
				LCD_clearScreen();     // Clear the LCD display
				last = 0;              // Reset last operand
				first = 0;             // Reset first operand
				op_flag = 0;           // Reset operator flag
			} else {
				op = input;            // Store the operator
				LCD_displayCharacter(op); // Display the operator on LCD
				op_flag = 1; // Set flag to indicate an operator has been selected
			}

		}
		_delay_ms(500);           // Delay to prevent button bouncing
	}
}
