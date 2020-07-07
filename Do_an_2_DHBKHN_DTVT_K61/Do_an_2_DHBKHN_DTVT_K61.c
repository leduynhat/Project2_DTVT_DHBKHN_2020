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

unsigned char push_button = 0;

int main(void)
{
	/************************************************************************/
	/* Phan 3.2. Dieu khien so cong ra                                      */
	/************************************************************************/
	//Do phan nay minh su dung code cua thay khong chay, nen minh da tu code lai
	//su dung ham PORT_new() thay vi PORT()
	
	//INIT();
	//PORT_new();
	
	/************************************************************************/
	/* Phan 3.3  Doc trang thai logic dau vao so                            */
	/************************************************************************/
	
	//INIT();
	//PB_2_LED();

	
	/************************************************************************/
	/* Phan 3.4 Do dien ap tuong tu va hien thi len man hinh LCD            */
	/************************************************************************/
	//Phan nay minh cung khong su dung duoc code cua thay nen da kiem tren trang
	//web tren de su dung
	
	//ADC_2_LCD_new();
	
	/************************************************************************/
	/* Phan 3.5 Giao tiep v?i may tinh qua chuan UART-USB                   */
	/************************************************************************/
	//char first_line[] = "Le Duy Nhat, 20163037, DTVT07-K61";
	//char second_line[] = "Vien Dien tu-Vien Thong, Truong DHBKHN";
	//LCD_Init();		/* Initialize LCD*/
	//LCD_String(first_line);/* Write string on 1st line of LCD*/
    //LCD_String_xy(1,0, second_line);
	//_delay_ms(1000);
	//
	//UART_init(9600);
	//
	//while(1)
	//{
		//UART_SendString(first_line);
		//UART_SendString("\n"); //newline
		//UART_SendString(second_line);
		//UART_SendString("\n"); //newline
		//LCD_Command(0x18);/* shift entire display left */
			///* 0x1C la dic phai
			 //0x18 la dic trai*/
		//_delay_ms(1000);
	//}
	/************************************************************************/
	/* Bai tap mo rong dieu khien dong co                                   */
	/************************************************************************/
	uint8_t count = 65;
	
	DDRD |= (1<<PD5);	/* Make OC1A pin as output */ 
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	while(1)
	{
		push_button = PB_CHECK();
		LED7_OUT(push_button);
		switch(push_button)
		{
			case 1: OCR1A = 65;	/* Set servo shaft at -90° position */
					_delay_ms(100);
					break;	
			case 2: OCR1A = 300;	/* Set servo shaft at -90° position */
					_delay_ms(100);
					break;	
			case 3: if(OCR1A >= 65 && OCR1A <= 290)
					{
						//count += 10; 
						OCR1A += 10; 
						_delay_ms(100);
						break;
					}
					else
					{
						_delay_ms(100);
						break;
					}		
					break;				
			case 4: if(OCR1A >= 75 && OCR1A <= 300)
					{
						//count -= 10; 
						OCR1A -= 10; 
						_delay_ms(100);
						break;
					}
					else
					{
						_delay_ms(100);
						break;
					}
					break;			
			//default: break;	
			//case 1: count = 65;  break;
			//case 2: count = 300; break;
			//default: break;
		}
		//OCR1A = count;
		//_delay_ms(2000);
	}
	return 0;
}