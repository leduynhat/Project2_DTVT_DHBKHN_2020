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
	
	//LCD_test(); //ham nay dung de test mam LCD
	ADC_2_LCD_new();
	
	return 0;
}