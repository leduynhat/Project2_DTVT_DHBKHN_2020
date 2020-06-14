/*************************************************************************************
 * ................................................................................. *
 * ......... Thu vien Function va Macro (rut gon) cho bo truyen thong UART ......... *
 * ......... Duoc thu nghiem tren phien ban WinAVR: 20070525 ------------- ......... *
 * ......... Soan thao va phat trien boi: ......... Dao Viet Hung -------- ......... *
 * ......... Email: ............................... hunget.bk@gmail.com -- ......... *
 * ......... H/P: ................................. 0917.515.242 --------- ......... *
 * ......... Phien ban: ........................... danh rieng cho H/P DA2 ......... *
 * ................................................................................. *
 *************************************************************************************/

#ifndef _AVR_HUNGET_UART_H_
#define _AVR_HUNGET_UART_H_

// Chi dan khai bao tan so

#ifndef FRE
# error "Ban phai khai bao tan so he thong truoc cac file header. Cu phap: #define FRE xx (Voi xx la tan so tinh bang MHz)."
#endif

// Ket thuc chi dan khai bao tan so

/*************************************************************************************/

// Cac function

void UART_INIT(unsigned int uart_ubrr, unsigned char uart_size, unsigned char uart_parity, unsigned char uart_stop);
void UART_TRAN_BYTE(unsigned char uart_data);
void UART_TRAN_STR(char *uart_str);

// -----------------------------------------------------------------------------------

void UART_INIT(unsigned int uart_ubrr, unsigned char uart_size, unsigned char uart_parity, unsigned char uart_stop)
{
	unsigned char uart_control = 0x80;

	// Khoi tao toc do baud

	UBRRH = (unsigned char)(uart_ubrr >> 8);
	UBRRL = (unsigned char)uart_ubrr;

	// Cho phep modul truyen, nhan

	UCSRB |= (1<<RXEN)|(1<<TXEN);

	// Dinh kich thuoc khung du lieu

	UCSRB &= ~(1<<UCSZ2);

	switch(uart_size)
	{
		case 8:	uart_control |= 0x06; break;
		case 7: uart_control |= 0x04; break;
		case 6: uart_control |= 0x02; break;
		case 5: break;
		case 9:
		{
			uart_control |= 0x06;
			UCSRB |= (1<<UCSZ2);
			break;
		}
		default: uart_control |= 0x06;
	}

	// Khoi tao modul parity

	if(uart_parity == 1)
		uart_control |= 0x30;
	if(uart_parity == 2)
		uart_control |= 0x20;

	// Chon so bit stop

	if(uart_stop == 2)
		uart_control |= 0x08;

	// Nap vao UCSRC

	UCSRC = uart_control;
}

void UART_TRAN_BYTE(unsigned char uart_data)
{
	while(!(UCSRA & (1<<UDRE)));

	UDR = uart_data;
}

void UART_TRAN_STR(char *uart_str)
{
	while(*uart_str)
	{
		UART_TRAN_BYTE(*uart_str);
		uart_str++;
	}
}

// Ket thuc cac function

#endif

/*************************************************************************************/
