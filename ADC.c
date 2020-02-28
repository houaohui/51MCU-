#include <stc12c5a60s2.h>
//#include <intrins.h>
unsigned dat;
sfr PLASF = 0x9d;
#define ADC_POWER 0x80
#define ADC_FLAG 0x10
#define ADC_START 0x08
#define ADC_SPEEDLL 0x00

void delay(unsigned int n)
{
	unsigned int x;
	while(n--)
	{
		x=5000;
		while(x--);
	}
}

void ADC_init()
{
	PLASF = 0x01;
	ADC_RES = 0;
	ADC_CONTR = ADC_POWER|ADC_SPEEDLL|ADC_START;
	delay(2);//4clocks
}

void main()
{
	ADC_init();
	IE=0xa0;
	while(1);
}
void adc() interrupt 5 using 1
{
	ADC_CONTR&=!ADC_FLAG;
	dat = ADC_RES;
	ADC_CONTR = ADC_POWER|ADC_SPEEDLL|ADC_START;
}
