/*
 * main.c
 *
 *  Created on: Feb 25, 2023
 *      Author: LENOVO
 */
/**********************************************************************************
 * 			INCLUDES
 *********************************************************************************/
#include "avr/delay.h"
#include "Mcu_HW.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Port_cfg.h"
#include "Port_int.h"


#include "KEYPAD_Init.h"
#include "TIMER0_int.h"
#include "GIE_init.h"

#include "LCD_priv.h"
#include "LCD_cfg.h"
#include "LCD_types.h"
#include "LCD_Init.h"

#include "DcMotor_cfg.h"
#include "DcMotor_init.h"
/**********************************************************************************
 * 			Functions Definitions
 *********************************************************************************/
extern const Port_ConfigType PORT_Config_Arr[PORT_PINS_CONFIG_ARR_SIZE];

u16 EnterValueKeyPad();






void main()
{
/***********************************************************************************
 * 	Initiations Sections
 *
 * 	PORT
 * 	LCD
 **********************************************************************************/
	Port_Init(PORT_Config_Arr);
	H_LCD_void_Init();
//	H_DcMotor_Void_Start(30, 5);
//	H_DcMotor_Void_ChangeDirection(LEFT_DIR);
/***********************************************************************************
 * 			Local Variables
 **********************************************************************************/
	u16 Local_FrequancyValue = 0 ;
	u16 Local_DutyCycleValue = 0 ;
	u8  Local_KeuypadValue = 0 ;

	while(1)
	{
		/*
		 * 	Enter the Freqancy
		 */
		H_LCD_void_sendString("Please Enter");
		H_LCD_void_gotoXY(1, 0);
		H_LCD_void_sendString("FREQ:");
		Local_FrequancyValue = EnterValueKeyPad();
		H_DcMotor_Void_STOP();
		/*
		 * 	Enter the Duty Cycle
		 */
		H_LCD_void_sendCommand(LCD_CLEAR_DISP);
		H_LCD_void_sendString("Please Enter");
		H_LCD_void_gotoXY(1, 0);
		H_LCD_void_sendString("Duty:");
		Local_DutyCycleValue = EnterValueKeyPad();

		/*
		 * 	Enter the Direction
		 */
		H_LCD_void_sendCommand(LCD_CLEAR_DISP);
		H_LCD_void_sendString("Enter DIR: ");
		H_LCD_void_gotoXY(1, 0);
		H_LCD_void_sendString("1-LEFT  2-RIGHT");

		do{
			Local_KeuypadValue = H_KEYPAD_u8_getPressedKey();

			if (Local_KeuypadValue == '1')
			{
			H_DcMotor_Void_ChangeDirection(LEFT_DIR);
			break;
			}
			else if(Local_KeuypadValue == '2')
			{
				H_DcMotor_Void_ChangeDirection(RIGHT_DIR);
				break;
			}
		}while(Local_KeuypadValue == NOT_PRESSED );


		/*
		 * 	Start Motor
		 */
		H_DcMotor_Void_Start(Local_FrequancyValue, Local_DutyCycleValue);
		H_LCD_void_sendCommand(LCD_CLEAR_DISP);

		Local_DutyCycleValue = 0 ;
		Local_FrequancyValue = 0 ;
	}

}


/***********************************************************************************
 * 					Enter Value of keypad and store it in u16
 **********************************************************************************/
u16 EnterValueKeyPad()
{
	u8 Local_KeyPadValue = 0 ;
	u8 Local_ValueArr[4] = {0};
	u8 Local_Counter = 0;
	u16 Local_FreqValue = 0 ;
	u16 Local_Multiply = 1 ;
	u8 Local_Temp = 0 ;
	/*
	 *  Enter the frequency into array
	 */
	do{
		Local_KeyPadValue = H_KEYPAD_u8_getPressedKey();

		if (Local_KeyPadValue != NOT_PRESSED )
		{
			/* Save Value to the array */
			Local_ValueArr[Local_Counter] = Local_KeyPadValue ;
			H_LCD_void_sendData( Local_ValueArr[Local_Counter]);

			if (Local_ValueArr[Local_Counter] == FINISH)
			{
				Local_Multiply /= 10 ;
				H_LCD_void_sendCommand(LCD_CLEAR_DISP);
				break;
			}

			Local_Multiply *= 10 ;
			Local_Counter ++ ;
		}

	}while(Local_KeyPadValue == NOT_PRESSED || Local_ValueArr[Local_Counter] != FINISH );

	Local_Temp = Local_Counter ;
	Local_Counter = 0 ;
	/* Convert Array to Init */

	do{
		Local_FreqValue += Local_Multiply*(Local_ValueArr[Local_Counter] - '0') ;
		Local_Counter ++ ;

		Local_Multiply /= 10 ;

	}while(Local_Temp != Local_Counter);


	return Local_FreqValue ;
}
