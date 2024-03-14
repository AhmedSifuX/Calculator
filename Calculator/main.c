/*
 * Calculator.c
 *
 * Created: 12/03/2024 05:23:16 
 * Author : Ahmed Hany
 */ 
#include <stdio.h>

#define F_CPU 16000000
#include "util/delay.h"



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"

#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#define MAX_LENGTH 100


int main(void)
{
	LCD_voidINIT();
	KPD_voidINIT();
	
	 char expression[MAX_LENGTH];
	 char postfix[MAX_LENGTH];
	 u8 index = 0;
	
	LCD_u8SendString("Welcome");
	_delay_ms(1000);
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	
	

	while (1) 
    {
		
		
		
		u8 pressedkey = KPD_NOT_PRESSED_KEY;
		do 
		{
			pressedkey = KPD_GetPressedKey();
		} while (pressedkey == KPD_NOT_PRESSED_KEY);
		
		switch(pressedkey)
		{
			case 'C':
			if (expression[0] == '\0')
			LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
			break;
			
			case '=':
			if (expression[0] == '\0')
			break;
			LCD_voidSendData('=');
			evaluate(expression);
			index=0;
			break;
			
			default:
			if (expression[0]== '\0')
			LCD_voidSendData(LCD_CLEAR_DISPLAY);
			
			expression[index] = pressedkey;
			LCD_voidSendData(pressedkey);
			index++;
			break;
			
			
		}
		expression[index] = '\0';

 	}
		
}

