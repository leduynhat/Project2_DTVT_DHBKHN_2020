/*
 * Do_an_2_DHBKHN_DTVT_K61.c
 *
 * Created: 6/12/2020 10:21:00 AM
 * Author: LeDuyNhat
 * GitHub:  https://github.com/leduynhat
 * Website: http://leduynhat.epizy.com
 * Code nay co tham khao tu trang https://www.electronicwings.com/avr-atmega/
 */ 
#define F_CPU 8000000UL
#define FRE 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "hunget_adc.h"
#include "hunget_lcd.h"
#include "hunget_uart.h"
#include "thu_vien_rieng.h"

int main(void)
{
	/************************************************************************/
	/* Phan 3.2. Dieu khien so cong ra                                      */
	/************************************************************************/
	//Do phan nay minh su dung code cua thay khong chay, nen minh da tu code lai
	//su dung ham PORT_new() thay vi PORT()
	
	//INIT();
	//PORT_new();
	//PORT();

	
	/************************************************************************/
	/* Phan 3.3  Doc trang thai logic dau vao so                            */
	/************************************************************************/
	
	//INIT();
	//uint8_t *button;
	//PB_2_LED(&button);

	
	/************************************************************************/
	/* Phan 3.4 Do dien ap tuong tu va hien thi len man hinh LCD            */
	/************************************************************************/
	//Phan nay minh cung khong su dung duoc code cua thay nen da kiem tren trang
	//web tren de su dung
	
	//ADC_2_LCD_new();
	
	/************************************************************************/
	/* Phan 3.5 Giao tiep v?i may tinh qua chuan UART-USB                   */
	/************************************************************************/
	
	//LCD init
	char first_line[] = "Le Duy Nhat, 20163037, DTVT07-K61";
	char second_line[] = "Vien Dien tu-Vien Thong, Truong DHBKHN";
	LCD_Init();		/* Initialize LCD*/
	LCD_String(first_line);/* Write string on 1st line of LCD*/
    LCD_String_xy(1,0, second_line);
	_delay_ms(1000);
	
	//UART init
	
	UART_init(9600);
	
	while(1)
	{
		UART_SendString(first_line);
		UART_SendString("\n"); //newline
		UART_SendString(second_line);
		LCD_Command(0x18);/* shift entire display left */
		_delay_ms(1000);
	}
	return 0;
}