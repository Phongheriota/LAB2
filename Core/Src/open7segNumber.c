/*
 * open7segNumber.c
 *
 *  Created on: Oct 4, 2024
 *      Author: phong
 */
#include"main.h"

void open7segNumber(int x)
{
	switch(x)
	{
	case 0:
		 HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		 HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		 HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		 HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		 break;
	case 1:
		 HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		 HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		 HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		 HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		 break;
	case 2:
			 HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			 HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			 HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			 HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			 break;

	case 3:
			 HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			 HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			 HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			 HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			 break;
	}
}

