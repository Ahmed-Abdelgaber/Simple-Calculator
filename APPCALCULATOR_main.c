/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: Ahmed Gaber
 */

#include"LSTD_TYPES.h"
#include "MDIO.h"
#include "HLCD.h"
#include "HKEYPAD.h"
#include "APPCALCULATOR.h"
#include <util/delay.h>

int main(void)
{

	HLCD_Void_config();
	HLCD_Void_init();
	HKEYPAD_Void_init();

	u8 pressedButton = NOTPRESSED;
	u32 Copy_U32_firstNumber = 0;
	u32 Copy_U32_secondNumber = 0;
	u8 Copy_U8_operation;
	u32 *ptrToCurrentVariable = &Copy_U32_firstNumber;
	while (1)
	{

		pressedButton = HKEYPAD_U8_getPressedKey();
		if (pressedButton != NOTPRESSED)
		{
			if (pressedButton == SET)
			{
				HLCD_Void_sendCommand(CLEAR_DISPLAY);
				Copy_U32_firstNumber = 0;
				Copy_U32_secondNumber = 0;
				ptrToCurrentVariable = &Copy_U32_firstNumber;
				Copy_U8_operation = 0;
			}
			else if (pressedButton == ADDITION
					|| pressedButton == SUBTRACTION
					|| pressedButton == MULTIPLICATION
					|| pressedButton == DIVIDE)
			{
				APP_Void_printPressedButton(pressedButton);
				ptrToCurrentVariable = &Copy_U32_secondNumber;
				Copy_U8_operation = pressedButton;
			}
			else if (pressedButton == EQUAL)
			{
				switch (Copy_U8_operation)
				{
				case ADDITION:
					APP_Void_additionOperation(&Copy_U32_firstNumber,
							&Copy_U32_secondNumber);
					break;
				case SUBTRACTION:
					APP_Void_subtractionOperation(&Copy_U32_firstNumber,
							&Copy_U32_secondNumber);
					break;
				case MULTIPLICATION:
					APP_Void_multiblicationOperation(&Copy_U32_firstNumber,
							&Copy_U32_secondNumber);
					break;
				case DIVIDE:
					APP_Void_divisionOperation(&Copy_U32_firstNumber,
							&Copy_U32_secondNumber);
					break;
				}
			}
			else
			{
				APP_Void_printPressedButton(pressedButton);
				APP_Void_storeEnteredValue(ptrToCurrentVariable, pressedButton);
			}
		}
		else
		{
			/*NOTHING*/
		}

	}
	return 0;
}

