/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Hany       ************************/
/********************  SWC: LCD             	************************/
/********************  LAYER: HAL               ************************/
/********************  VERSION: 1.1             ************************/
/********************  DATE: 7/3/2024           ************************/
/***********************************************************************/
/***********************************************************************/

#define  F_CPU 16000000
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


static void sendEnablePulse(void)
{
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_E,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_E,DIO_PIN_LOW);

}

static void send4Bits(u8 copy_u8value)
{
	
	u8 local_u8shift=0;
	local_u8shift=GET_BIT(copy_u8value,0);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_DATA_PIN0,local_u8shift);

	local_u8shift=GET_BIT(copy_u8value,1);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_DATA_PIN1,local_u8shift);
	
	local_u8shift=GET_BIT(copy_u8value,2);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_DATA_PIN2,local_u8shift);
	
	local_u8shift=GET_BIT(copy_u8value,3);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_DATA_PIN3,local_u8shift);

}


void LCD_voidINIT(void)
{
	/*LCD PINS*/
	
	/*CTRL*/
	//RS
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_CTRL_RS,DIO_PIN_OUTPUT);
	//RW
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_CTRL_RW,DIO_PIN_OUTPUT);
	//E
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_CTRL_E,DIO_PIN_OUTPUT);
	
	
	/*DATA PINS 8_BIT*/
	//DIO_u8SetPortDirection(DIO_PORTA,DIO_PORT_OUTPUT);
	
	DIO_u8SetPinDirection(LCD_DATA_PORT,LCD_DATA_PIN0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(LCD_DATA_PORT,LCD_DATA_PIN1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(LCD_DATA_PORT,LCD_DATA_PIN2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(LCD_DATA_PORT,LCD_DATA_PIN3,DIO_PIN_OUTPUT);
	/*---------------------------------------------------------*/
	
	/*wait for more than 30ms*/
	_delay_ms(40);
	
	#if LCD_MODE == EIGHT_BIT

	/*function set : N(number of lines) = 1 :2lines  font=1 5*11 */
	LCD_voidSendCommand(0b00111100);
	//sendEnablePulse();
	/*Display: D=1 cursor=1 blink =1*/
	LCD_voidSendCommand(0b00001110);
	//sendEnablePulse();
	/*clear display*/
	LCD_voidSendCommand(0b00000001);
	//sendEnablePulse();
	#elif LCD_MODE == FOUR_BIT

	/*function set  n=1 f=1     0b00111100 */
	send4Bits(0b0010);
	sendEnablePulse();
	send4Bits(0b0010);
	sendEnablePulse();
	send4Bits(0b1100);
	sendEnablePulse();


	#else
	#error "LCD_MODE_CONFIGURATION_FILE "
	#endif
	
	/*Display: D=1 cursor=1 blink =0*/
	LCD_voidSendCommand(0b00001100);
	//sendEnablePulse();
	/*clear display*/
	LCD_voidSendCommand(0b00000001);
	//sendEnablePulse();
	/*------------------------------------------*/

}
void LCD_voidSendCommand(u8 command)
{
		//CTRL
	//RS COMMAND=0 DATA=1
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_RS,DIO_PIN_LOW);

	//RW WRITE =0 READ=1
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_RW,DIO_PIN_LOW);

	/*send command*/
	#if LCD_MODE == EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,command);
    sendEnablePulse();
	
	#elif LCD_MODE == FOUR_BIT
	
	send4Bits(command>>4);
	sendEnablePulse();
	send4Bits(command);
	sendEnablePulse();


	#else
	#error "LCD_MODE_CONFIGURATION_FILE "
	#endif
	//ENABLE PULSE
	//sendEnablePulse();
}
void LCD_voidSendData(u8 Data)
{
	//CTRL
	//RS COMMAND=0 DATA=1
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_RS,DIO_PIN_HIGH);

	//RW WRITE =0 READ=1
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_CTRL_RW,DIO_PIN_LOW);

	/*send command*/
	#if LCD_MODE == EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,Data);
	sendEnablePulse();
	
	#elif LCD_MODE == FOUR_BIT
	
	send4Bits(Data>>4);
	sendEnablePulse();
	send4Bits(Data);
	sendEnablePulse();


	#else
	#error "LCD_MODE_CONFIGURATION_FILE "
	#endif
	//ENABLE PULSE
	//sendEnablePulse();
}
u8 LCD_u8SendString(const u8* u8String)
{
	u8 local_u8ErrorState=OK;
	u8 local_u8StringIndex=0;
	
	if(u8String != NULL)
	{
		while( u8String[local_u8StringIndex]!= '\0' )
		{
			LCD_voidSendData(u8String[local_u8StringIndex]);
			local_u8StringIndex++;
		}
	}
	else
	local_u8ErrorState = NOK;
	
	return local_u8ErrorState;
}

u8 LCD_u8SetPosXY(u8 PosX, u8 PosY)
{
	u8 Local_Error_State = OK;
	u8 Local_DDRAM_address = 0;
	
	if((PosX == 0) || (PosX == 1))
	Local_DDRAM_address = (PosY + 0x40*PosX);
	else
	Local_Error_State = NOK;
	
	LCD_voidSendCommand(Local_DDRAM_address+128);
	
}
void LCD_voidSendSpecialCharacter(u8 *ptru8Special,u8 block,u8 PosX,u8 PosY)
{
	u8 Local_CGRAM_address=0;
	u8 Local_Index=0 ;
	
	Local_CGRAM_address=block*8;
	LCD_voidSendCommand(Local_CGRAM_address+64);
	
	for(Local_Index = 0 ;Local_Index<8; Local_Index++)
	{
		LCD_voidSendData(ptru8Special[Local_Index]);
	}
	LCD_u8SetPosXY(PosX,PosY);
	LCD_voidSendData(block);
}


void LCD_voidWriteNumber(u32 number)
{
	u32 local_reversed=1;

	if(number==0)
	{
		LCD_voidSendData('0');
	}
	else
	{
		//Reverse Number
		while (number != 0)
		{
			local_reversed=local_reversed*10 + (number%10);
			number/=10;
		}
		
		do
		{
			LCD_voidSendData((local_reversed % 10) + '0');
			local_reversed/=10;
		}
		while(local_reversed != 1);
	}
}