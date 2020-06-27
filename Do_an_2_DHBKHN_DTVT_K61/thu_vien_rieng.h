/*
 * thu_vien_rieng.h
 *
 * Created: 3/15/2020 9:05:49 AM
 *  Author: dell
 */ 


#ifndef THU_VIEN_RIENG_H_
#define THU_VIEN_RIENG_H_

#define LCD_Data_Dir DDRC		/* Define LCD data port direction */
#define LCD_Command_Dir DDRD		/* Define LCD command port direction register */
#define LCD_Data_Port PORTC		/* Define LCD data port */
#define LCD_Command_Port PORTD		/* Define LCD data port */
#define RS PD6				/* Define Register Select (data/command reg.)pin */
#define RW PD5					/* Define Read/Write signal pin */
#define EN PD7					/* Define Enable signal pin */
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

unsigned char push_button;

void INIT();
void PORT();
void LED7_OUT(uint8_t num);
void DELAY_MS(unsigned int mili_count);
void PB_2_LED();
uint8_t PB_CHECK();
void ADC_2_LCD();
void ADC_2_LCD_new();
void UART();
void LCD4_DIS_SHIFT(unsigned char lcd4_direct, unsigned char lcd4_step);


void PORT_new();
void LED7_OUT_new(uint8_t num);
void LCD_Command(unsigned char cmnd);
void LCD_Char (unsigned char char_data);	/* LCD data write function */
void LCD_Init (void);			/* LCD Initialize function */
void LCD_String (char *str)	;	/* Send string to LCD function */
void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */;
void LCD_Clear();
void LCD_test();


/************************************************************************/
/* Ham duoc cac thay co cung cap san                                    */
/************************************************************************/
void INIT()
{
	//Khai bao trang thai output cho 8 chan led det
	DDRD |= 0xFF;
	PORTD |= 0x00;
	//LED 7 thanh
	DDRC |= 0xFF;
	PORTC |= 0x00;
	//Khoi tao cho chan ADC
	DDRA = 0x00;
	PORTA = 0x00;
	
	//ADC_PRES(128);
	//ADC_AVCC();
	//ADC_IN(0);
}
	
void PORT()
{
	uint8_t led_shift = 0xFF;
	uint8_t led_7_count = 0x00;
	
	for(;;)
	{
		PORTD = led_shift;
		if(led_shift != 0)
			led_shift = led_shift << 2;
		else
			led_shift = 0xFF;
		LED7_OUT(led_7_count);
		
		PORTC ^= (1 << PC3);
		led_7_count += 2;
		if (led_7_count > 8)
		{
			led_7_count = 0;
		}
		DELAY_MS(500);
	}
}

void LED7_OUT(uint8_t num)
{
	uint8_t temp = PORTC;
	temp &= 0b00001000;
	
	switch(num)
	{
		case 0: temp |= 0b10000000; break;
		case 1: temp |= 0b11100011; break;
		case 2: temp |= 0b01000100; break;
		case 3: temp |= 0b01000001; break;
		case 4: temp |= 0b00100011; break;
		case 5: temp |= 0b00010001; break;
		case 6: temp |= 0b00010000; break;
		case 7: temp |= 0b11000011; break;
		case 8: temp |= 0b00000000; break;
		case 9: temp |= 0b00000001; break;
	}
	PORTC = temp;
}
void DELAY_MS(unsigned int mili_count)
{
	unsigned int i,j;
	mili_count = mili_count * FRE;
	for (i = 0; i<mili_count; i++)
		for(j = 0; j < 53; j++)
		{
			//NULL
		}
}
void PB_2_LED()
{
	for(;;)
	{
		push_button = PB_CHECK();
		LED7_OUT(push_button);
		switch(push_button)
		{
			case 1: PORTD = 0b11111100; break;	
			case 2: PORTD = 0b11110011; break;	
			case 3: PORTD = 0b11001111; break;
			case 4: PORTD = 0b00111111; break;			
			default: PORTD = 0xFF;	
		}
	}
}
uint8_t PB_CHECK()
{
	if ((PINB & 0x0F) != 0x0F)
	{
		if(!(PINB & (1<<PB0)))
			return 1;
		
		if(!(PINB & (1<<PB1)))
			return 2;
			
		if(!(PINB & (1<<PB2)))
			return 3;
			
		if(!(PINB & (1<<PB3)))
			return 4;
	}
	return push_button;
}
void ADC_2_LCD()
{
	DDRD |= (1<<PD5);
	PORTD &= ~(1<<PD5);
	PORTC |= 0x0F;
	
	LCD4_INIT(0,0);
	
	LCD4_CUR_GOTO(1,0);
	LCD4_OUT_STR("ADC&LCD byDNhat");
	
	LCD4_CUR_GOTO(2,0);
	LCD4_OUT_STR("ADC0: 0000/1024");
	
	for (;;)
	{
		ADC_STA_CONVERT();
		LCD4_CUR_GOTO(2,6);
		LCD4_OUT_DEC(ADC,4);
		DELAY_MS(200);
	}
}
void UART()
{
	UART_INIT(51, 8, 0 ,1);
	DDRD |= (1<PD5);
	PORTD &= ~(1<<PD5);
	PORTC |= 0x0F;
	
	LCD4_INIT(0,0);
	
	LCD4_CUR_GOTO(1,0);
	LCD4_OUT_STR("Le Duy Nhat, 20163037, DTVT07-K61");
	LCD4_CUR_GOTO(2,0);
	LCD4_OUT_STR("Vien DTVT, Truong DHBK Ha Noi");
	
	DELAY_MS(1000);
	
	while(1)
	{
		UART_TRAN_STR("Le Duy Nhat, 20163037, DTVT07-k61");
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		
		UART_TRAN_STR("Vien DTVT, Truong DHBK Ha Noi");
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		
		//DELAY_MS(1000);
		_delay_ms(1000);
		
		LCD4_DIS_SHIFT(1, 1);
	}
}
void LCD4_DIS_SHIFT(unsigned char lcd4_direct, unsigned char lcd4_step)
{
	unsigned char i;
	if(lcd4_direct == 0)
		for(i = 0; i< lcd4_step; i++)
			LCD4_OUT_CMD(0x1C);
	else
		for(i = 0; i< lcd4_step; i++)
			LCD4_OUT_CMD(0x18);
}


/************************************************************************/
/* Ham moi do minh them vao                                             */
/************************************************************************/
void LED7_OUT_new(uint8_t num)
{

	char array[]={0x88,0xEB,0x4C,0x49,0x2B,0x19,0x18,0xCB,0x08,0x09};
					/* write hex value for CA display from 0 to 9 */ 
   
    while(1)
    {
		for(int i=0;i<10;i++)
		{
			PORTC = array[num]; /* write data on to the LED port */
			DELAY_MS(1000); /* wait for 1 second */ 
		}
    }
}
void PORT_new(){
	char array[]={0x88,0xEB,0x4C,0x49,0x2B,0x19,0x18,0xCB,0x08,0x09};
					/* write hex value for CA display from 0 to 9 */ 
    uint8_t led_shift = 0xFF;
    while(1)
    {
		for(int i=0;i<5;i++)
		{
			PORTD = led_shift;
			if(led_shift != 0 && i < 8)
				led_shift = led_shift << 2;
			else
				led_shift = 0xFF;
			
			PORTC = array[2*i]; /* write data on to the LED port */
			_delay_ms(1000); /* wait for 1 second */ 
		}	
    }
}	
void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}
void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}
void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}
void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}
void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}
void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}
void LCD_shift(){
	int shift,i;
	char first_line[] = "Le Duy Nhat, 20163037, DTVT07-K61";
	char second_line[] = "Vien Dien tu-Vien Thong, Truong DHBKHN";
	LCD_Init();		/* Initialize LCD*/
	LCD_String(first_line);/* Write string on 1st line of LCD*/
    LCD_String_xy(1,0, second_line);
	shift = 30;	/* Number of time shifts count=30 */
	_delay_ms(1000);
	
	while(1)
	{
		for(i=0;i<shift;i++)
		{
			LCD_Command(0x1c);/* shift entire display right */
			_delay_ms(1000);
		}			
		shift=30;/* number of time shifts 30 */
			
		for(i=0;i<30;i++)
		{
			LCD_Command(0x18);/* shift entire display left */
			_delay_ms(1000);
		}
	}
}


void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

 
void ADC_2_LCD_new(){
	char String[5];
	int value;

	ADC_Init();
	LCD_Init();			/* Initialization of LCD */
	LCD_String("Test ADC & LCD");	/* Write string on 1st line of LCD */
	LCD_String_xy(1, 0, "ADC0:     /1023" );
	while(1)
	{
		LCD_Command(0xc4);	/* LCD16x2 cursor position */
		value=ADC_Read(0);	/* Read ADC channel 0 */
		itoa(value,String,10);	/* Integer to string conversion */ 
		LCD_String_xy(1, 6, String);						
		_delay_ms(500);
	}
}


void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
	UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/
}

unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	return(UDR);			/* Return the byte*/
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);	
		j++;
	}
}
#endif /* THU_VIEN_RIENG_H_ */