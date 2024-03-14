/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Hany       ************************/
/********************  SWC: KPD             	************************/
/********************  LAYER: HAL               ************************/
/********************  VERSION: 1.0             ************************/
/********************  DATE:7/3/2024            ************************/
/***********************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"

void KPD_voidINIT(void)
{
	/*initial value for row high*/
	DIO_u8SetPinDirection(KPD_PORT_ROW,KPD_ROW0,DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT_ROW,KPD_ROW1,DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT_ROW,KPD_ROW2,DIO_PIN_INPUT);
	DIO_u8SetPinDirection(KPD_PORT_ROW,KPD_ROW3,DIO_PIN_INPUT);
	
	/*PULLUP*/
	DIO_u8SetPinValue(KPD_PORT_ROW,KPD_ROW0,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_ROW,KPD_ROW1,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_ROW,KPD_ROW2,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_ROW,KPD_ROW3,DIO_PIN_HIGH);
	
	DIO_u8SetPinDirection(KPD_PORT_COL,KPD_COL0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT_COL,KPD_COL1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT_COL,KPD_COL2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT_COL,KPD_COL3,DIO_PIN_OUTPUT);
	
	DIO_u8SetPinValue(KPD_PORT_COL,KPD_COL0,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_COL,KPD_COL1,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_COL,KPD_COL2,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT_COL,KPD_COL3,DIO_PIN_HIGH);
	
}
u8 KPD_GetPressedKey(void)
{
	u8 local_u8PressedKey=0xff;
	u8 local_u8KPD_Arr[KPD_ROW_NUMBER][KPD_COL_NUMBER]=KPD_arr;
	u8 local_u8ROW_Arr[KPD_ROW_NUMBER]={KPD_ROW0,KPD_ROW1,KPD_ROW2,KPD_ROW3};
	u8 local_u8COL_Arr[KPD_COL_NUMBER]={KPD_COL0,KPD_COL1,KPD_COL2,KPD_COL3};
	u8 local_u8Index_col=0,local_u8Index_row=0;

	u8 local_u8RowState=DIO_PIN_HIGH;


	/*
	LOOP


	*/
	for(local_u8Index_col = 0 ; local_u8Index_col < KPD_COL_NUMBER ; local_u8Index_col++ )
	{
		
		/*Activate column by low*/
		DIO_u8SetPinValue(KPD_PORT_COL,local_u8COL_Arr[local_u8Index_col],DIO_PIN_LOW);
		
		/*check R0--->R4 IF pressed retrun pressedKey*/
		for(local_u8Index_row = 0 ; local_u8Index_row < KPD_ROW_NUMBER ; local_u8Index_row++ )
		{
			/*get row value*/
			DIO_u8GetPinValue(KPD_PORT_ROW,local_u8ROW_Arr[local_u8Index_row],&local_u8RowState);
			if(local_u8RowState == DIO_PIN_LOW)
			{
				
				/*bus*/
				while(local_u8RowState == DIO_PIN_LOW){
					DIO_u8GetPinValue(KPD_PORT_ROW,local_u8ROW_Arr[local_u8Index_row],&local_u8RowState);
				}
				local_u8PressedKey=local_u8KPD_Arr[local_u8Index_row][local_u8Index_col];
				return local_u8PressedKey;
			}
			
		}
		
		/*Deactivate current column*/
		DIO_u8SetPinValue(KPD_PORT_COL,local_u8COL_Arr[local_u8Index_col],DIO_PIN_HIGH);
		
	}

	return local_u8PressedKey;

}