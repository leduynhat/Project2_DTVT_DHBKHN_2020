/*************************************************************************************
 * ................................................................................. *
 * ......... Thu vien Function va Macro (rut gon) cho LCD giao dien 4-bit. ......... *
 * ......... Duoc thu nghiem tren phien ban WinAVR: 20070525 ------------- ......... *
 * ......... Soan thao va phat trien boi: ......... Dao Viet Hung -------- ......... *
 * ......... Email: ............................... hunget.bk@gmail.com -- ......... *
 * ......... H/P: ................................. 0917.515.242 --------- ......... *
 * ......... Phien ban: ........................... danh rieng cho H/P DA2 ......... *
 * ................................................................................. *
 *************************************************************************************

Cach su dung cac ham:

	LCD4_CUR_DEC_ON();

	- Tang con tro va dich khung hien thi sau moi lan in ra ky tu

	LCD4_CUR_DEC_OFF();
	
	- Tang con tro, khung hien thi dung yen sau moi lan in ra ky tu

	LCD4_CUR_INC_ON();

	- Giam con tro va dich khung hien thi sau moi lan in ra ky tu

	LCD4_CUR_INC_OFF();
	
	- Giam con tro, khung hien thi dung yen sau moi lan in ra ky tu

	LCD4_CUR_GOTO(hang, cot);
	
	- Dieu khien con tro nhay toi mot vi tri

	LCD4_INIT(con_tro_gach_duoi,con_tro_nhap_nhay);

	- Khoi tao man LCD
	- Quyet dinh dang cua con tro se duoc hien thi voi bat (1) va tat (0)

	LCD4_CLR();
	
	- Xoa toan bo man hien thi

	LCD4_HOME();
	
	- Dua con tro va khung hien thi ve vi tri 0,0

	LCD4_OUT_CMD(ma_lenh);
	
	- Xuat lenh sang LCD

	LCD4_OUT_DATA(du_lieu);
	
	- Xuat du lieu sang LCD

	LCD4_OUT_STR("xau_ki_tu");
	
	- In mot xau ky tu dang luu trong RAM
	
	LCD4_OUT_DEC(so_can_in, k_gian_in);
	
	- In ra mot so tu nhien

	LCD4_DELAY(thoi_gian_tinh_theo_100us);

	- Ham tre dung rieng cho LCD

 *************************************************************************************/

#ifndef _AVR_HUNGET_LCD_4BIT_H_
#define _AVR_HUNGET_LCD_4BIT_H_

#include <avr/pgmspace.h>

// Chi dan khai bao tan so

#ifndef FRE

#error "Ban phai khai bao tan so he thong truoc cac file header. Cu phap: #define FRE xx (Voi xx la tan so tinh bang MHz)."

#endif

// Ket thuc chi dan khai bao tan so

/*************************************************************************************/

// Cac macro

// -----------------------------------------------------------------------------------

// Cac khai bao can thiet truoc khi su dung

//	-------------------------------------------------------------------------------------------------
//	|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  11 |  12 |  13 |  14 |  15 |  16 |
//	-------------------------------------------------------------------------------------------------
//	| Vss | Vdd | Vo  | RS  | R/W |  E  |  -  |  -  |  -  |  -  |  D4 |  D5 |  D6 |  D7 |  A  |  K  |
//	-------------------------------------------------------------------------------------------------
//	|        -        |     Control     |           -           |          Data         |     -     |
//	-------------------------------------------------------------------------------------------------

// Port lenh chua cac chan noi toi chan RS va E cua LCD

#define lcd4_control_PORT	PORTD
#define lcd4_control_DDR 	DDRD

#define RS					PD6
#define E					PD7

// Port du lieu noi toi cac chan Data cua LCD

#define lcd4_data_PORT		PORTC
#define lcd4_data_DDR		DDRC


// Ket thuc cac khai bao can thiet truoc khi su dung

// -----------------------------------------------------------------------------------

#define LCD4_CUR_DEC_ON()	LCD4_OUT_CMD(0x05)
#define LCD4_CUR_DEC_OFF()	LCD4_OUT_CMD(0x04)
#define LCD4_CUR_INC_ON()	LCD4_OUT_CMD(0x07)
#define LCD4_CUR_INC_OFF()	LCD4_OUT_CMD(0x06)

// Ket thuc cac macro

/*************************************************************************************/

// Cac function

void LCD4_INIT(unsigned char lcd4_cur_underline, unsigned char lcd4_cur_blink);

void LCD4_OUT_CMD(unsigned char lcd4_cmd);
void LCD4_OUT_DATA(unsigned char lcd4_data);

void LCD4_CLR();
void LCD4_HOME();

void LCD4_CUR_GOTO(unsigned char lcd4_row, unsigned char lcd4_col);
void LCD4_OUT_STR(char *lcd4_str);
void LCD4_OUT_DEC(unsigned long int lcd4_n, unsigned char lcd4_length);

void LCD4_DELAY(unsigned int lcd4_n);

// -----------------------------------------------------------------------------------

void LCD4_INIT(unsigned char lcd4_cur_underline, unsigned char lcd4_cur_blink)
{
	unsigned char lcd4_cur_mode = 0x0C;
	unsigned char lcd4_i;
	
	// Xac dinh dang con tro

	if(lcd4_cur_underline) lcd4_cur_mode |= (1<<1);
	if(lcd4_cur_blink) lcd4_cur_mode |= (1<<0);

	LCD4_DELAY(400);						// Cho it nhat 40 ms cho LCD on dinh

	// Cau hinh cac chan du lieu la dau ra

	lcd4_control_DDR |= (1<<E);
	lcd4_control_DDR |= (1<<RS);

	lcd4_data_DDR |= 0xF0;
	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0

	// Gui lien tiep 3 lenh 0x30 de khoi tao

	for(lcd4_i=0;lcd4_i<3;lcd4_i++)
	{
		lcd4_control_PORT &= ~(1<<RS);
		lcd4_control_PORT |= (1<<E);
		lcd4_data_PORT |= 0x30;
		lcd4_data_PORT |= 0x30;				// Xuat du lieu hai lan
		lcd4_control_PORT &= ~(1<<E);	
		LCD4_DELAY(2);						// Tre it nhat 160 us de hoan thanh lenh
	}

	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0
	lcd4_control_PORT &= ~(1<<RS);
	lcd4_control_PORT |= (1<<E);
	lcd4_data_PORT |= 0x20;					// Xac dinh bus 4 bit
	lcd4_data_PORT |= 0x20;
	lcd4_control_PORT &= ~(1<<E);
	LCD4_DELAY(41);
						
	LCD4_OUT_DATA(0x28);					// Hai dong, ma tran 5x7, bus 4 bit.
	LCD4_DELAY(41);							// Tre it nhat 4.1 ms de hoan thanh lenh

	LCD4_OUT_CMD(lcd4_cur_mode);			// Bat hien thi, va khoi tao con tro.
	LCD4_DELAY(41);							// Tre mot luc

	LCD4_CLR();
	LCD4_HOME();
}

void LCD4_OUT_CMD(unsigned char lcd4_cmd)
{
	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0
	lcd4_control_PORT &= ~(1<<RS);
	lcd4_control_PORT |= (1<<E);
	lcd4_data_PORT |= (lcd4_cmd & 0xF0);	// Xuat 4 bit cao
	lcd4_data_PORT |= (lcd4_cmd & 0xF0);
	lcd4_control_PORT &= ~(1<<E);
	LCD4_DELAY(1);							// Tre mot luc. 100 us

	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0
	lcd4_control_PORT &= ~(1<<RS);
	lcd4_control_PORT |= (1<<E);
	lcd4_data_PORT |= ((lcd4_cmd << 4) & 0xF0);		// Xuat 4 bit thap
	lcd4_data_PORT |= ((lcd4_cmd << 4) & 0xF0);
	lcd4_control_PORT &= ~(1<<E);
	LCD4_DELAY(2);							// Tre it nhat 160 us de hoan thanh lenh
}

void LCD4_OUT_DATA(unsigned char lcd4_data)
{
	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0
	lcd4_control_PORT |= (1<<RS);
	lcd4_control_PORT |= (1<<E);
	lcd4_data_PORT |= (lcd4_data & 0xF0);	// Xuat 4 bit cao
	lcd4_data_PORT |= (lcd4_data & 0xF0);
	lcd4_control_PORT &= ~(1<<E);
	LCD4_DELAY(1);							// Tre mot luc
	
	lcd4_data_PORT &= 0x0F;					// Xoa bus 4 bit ve 0
	lcd4_control_PORT |= (1<<RS);
	lcd4_control_PORT |= (1<<E);
	lcd4_data_PORT |= ((lcd4_data << 4) & 0xF0);	// Xuat 4 bit thap
	lcd4_data_PORT |= ((lcd4_data << 4) & 0xF0);
	lcd4_control_PORT &= ~(1<<E);
	LCD4_DELAY(2);							// Tre it nhat 160 us de hoan thanh lenh
}

void LCD4_CLR()
{
	LCD4_OUT_CMD(0x01);
	LCD4_DELAY(41);							// Tre it nhat 4.1 ms de hoan thanh lenh
}

void LCD4_HOME()
{
	LCD4_OUT_CMD(0x02);
	LCD4_DELAY(41);							// Tre it nhat 4.1 ms de hoan thanh lenh
}

void LCD4_CUR_GOTO(unsigned char lcd4_row, unsigned char lcd4_col)
{
	if(lcd4_row == 2)
		LCD4_OUT_CMD(0xC0 + lcd4_col);
	else
		LCD4_OUT_CMD(0x80 + lcd4_col);
}

void LCD4_OUT_STR(char *lcd4_str)
{
	while(*lcd4_str)
	{
		LCD4_OUT_DATA(*lcd4_str);
		lcd4_str++;
	}
}

void LCD4_OUT_DEC(unsigned long int lcd4_n, unsigned char lcd4_length)
{
	unsigned char lcd4_temp[lcd4_length];
	unsigned char i;
	for(i=0;i<lcd4_length;i++)
	{
		lcd4_temp[i] = (lcd4_n % 10) + 0x30;
		lcd4_n = lcd4_n / 10;
	}
	for(i=lcd4_length;i>0;i--)
	{
		LCD4_OUT_DATA(lcd4_temp[i-1]);
	}
}

void LCD4_DELAY(unsigned int lcd4_n)
{
	unsigned int i;
	unsigned char j;
	lcd4_n = lcd4_n * FRE;
	for(i=0;i<lcd4_n;i++)
		for(j=0;j<6;j++);
}

// Ket thuc cac function

#endif /* _AVR_HUNGET_LCD_4BIT_H_ */

/*************************************************************************************/
