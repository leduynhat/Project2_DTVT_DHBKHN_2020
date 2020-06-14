/*************************************************************************************
 * ................................................................................. *
 * ......... Thu vien Function va Macro (rut gon) cho bo ADC cua VDK AVR - ......... *
 * ......... Duoc thu nghiem tren phien ban WinAVR: 20070525 ------------- ......... *
 * ......... Soan thao va phat trien boi: ......... Dao Viet Hung -------- ......... *
 * ......... Email: ............................... hunget.bk@gmail.com -- ......... *
 * ......... H/P: ................................. 0917.515.242 --------- ......... *
 * ......... Phien ban: ........................... danh rieng cho H/P DA2 ......... *
 * ................................................................................. *
 *************************************************************************************

	Cac thu tuc can lam:

	- Cau hinh cac chan vao
	- Chon he so chia tan
	- Chon dien ap tham chieu
	- Chon kenh
	- Cho phep bien doi va doc ket qua

 *************************************************************************************

	ADC_PRES(he_so_chia_tan);

	ADC_AVCC();								// Dien ap tham chieu la VCC
	ADC_2V56();								// Dien ap tham chieu ben trong 2.56V
	ADC_AREF();								// Dien ap tham chieu mac dinh la dien ap tren chan AREF

	ADC_IN(kenh_ADC);
	ADC_ALIGN_L();							// Ket qua can le trai
	ADC_ALIGN_R();							// Ket qua can le phai
	ADC_AUTO();								// Tu dong bien doi
	ADC_STA_CONVERT();						// Bat dau mot bien doi

 *************************************************************************************/

#define ADC_PRES(factor) \
{ \
	ADCSRA |= (1<<ADEN); \
	switch(factor) \
	{ \
		case 2: ADCSRA |= (1<<ADPS0); break; \
		case 4: ADCSRA |= (1<<ADPS1); break; \
		case 8: ADCSRA |= (1<<ADPS0)|(1<<ADPS1); break; \
		case 16: ADCSRA |= (1<<ADPS2); break; \
		case 32: ADCSRA |= (1<<ADPS0)|(1<<ADPS2); break; \
		case 64: ADCSRA |= (1<<ADPS1)|(1<<ADPS2); break; \
		case 128: ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); break; \
		/* Mac dinh la 32 */ \
		default: ADCSRA |= (1<<ADPS0)|(1<<ADPS2); \
	} \
}

/************************************************************************************/

// Chon dien ap tham chieu. Neu khong chon thi dien ap tham chieu
// mac dinh la dien ap tren chan AREF.

#define ADC_AVCC() ADMUX |= (1<<REFS0)
#define ADC_2V56() ADMUX |= (1<<REFS1)|(1<<REFS0)
#define ADC_AREF() ADMUX &= ~((1<<REFS1)|(1<<REFS0))

/*************************************************************************************/

// Chon dau vao single ended. Neu khong chon thi dau vao mac dinh la dau ADC0

#define ADC_IN(channel) \
{ \
	unsigned char adc_input = 0; \
	adc_input = ADMUX & 0xE0; \
	adc_input |= (channel); \
	ADMUX = adc_input; \
}

#define ADC_ALIGN_L() 		ADMUX |= (1<<ADLAR)
#define ADC_ALIGN_R() 		ADMUX &= ~(1<<ADLAR)
#define ADC_AUTO() 			ADCSRA |= (1<<ADATE)
#define ADC_STA_CONVERT() 	ADCSRA |= (1<<ADSC)

/*************************************************************************************/
