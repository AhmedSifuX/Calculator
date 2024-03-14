/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Hany       ************************/
/********************  SWC: LCD             	************************/
/********************  LAYER: HAL               ************************/
/********************  VERSION: 1.0             ************************/
/********************  DATE:6/3/2024           ************************/
/***********************************************************************/
/***********************************************************************/



#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_CLEAR_DISPLAY 1


void LCD_voidINIT(void);
void LCD_voidSendCommand(u8 command);
void LCD_voidSendData(u8 Data);

u8 LCD_u8SendString(const u8* u8String);
u8 LCD_u8SetPosXY(u8 PosX, u8 PosY);
void LCD_voidSendSpecialCharacter(u8 *ptru8Special,u8 block,u8 PosX,u8 PosY);


void LCD_voidWriteNumber(u32 number);




#endif