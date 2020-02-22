#include <stc12c5a60s2.h>
sbit DS = P3^5; //1_wire

void delay(unsigned int us)
{
	while(us--);
}

//³õÊ¼»¯³ÌÐò
bit ds_init()
{
	bit i;
	DS=1;
	delay(1);
	DS=0;
	delay(998);//ÑÓÊ±480usÒÔÉÏ£¬ds18b20½«±»¸´Î»
	DS=1;
	delay(59);//15~60us,µÈ´ý
	i=DS;
	delay(300);//²ÉÑùÖ®ºóµÈ´ý60~240us
	DS=1;
	delay(1);
	return (i);
}

//Ð´Ò»¸ö×Ö½Ú
void write_byte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DS=0;
		delay(1);
		DS=dat&0x01;
		delay(150);//ÑÓÊ±60usÒÔÉÏ
		DS=1; //ÊÍ·Å×ÜÏß×¼±¸ÏÂ´ÎÊý¾ÝÐ´Èë
		delay(1);//1us
		dat >>= 1;
	}
}
//¶ÁÒ»¸ö×Ö½Ú
unsigned char read_byte()
{
	unsigned char i,j,dat;
	for(i=0;i<8;i++)
	{
		DS=0;//²úÉú¶ÁÊ±Ðò
		delay(1);//1us
		DS=1;//ÊÍ·ÅÖÐÏß²ÉÑù
		delay(1);//1us
		j=DS;
		delay(150);//60usÒÔÉÏ
		DS=1;
		delay(1);//1us
		dat=(j<<7)|(dat>>1);
	}
	return(dat);
}
bit Start18B20()
{
	bit ack;
	ack=ds_init();
	if(ack==0)
	{
		write_byte(0xcc);
		write_byte(0x44);
	}
	return(~ack);
}


bit Get18B20Temp(int *temp)
{
	bit ack;
	unsigned char LSB,MSB;
	EA=0;
	ack=ds_init();
	if(ack==0)
	{
		write_byte(0xcc);
		write_byte(0xbe);
		LSB=read_byte();
		MSB=read_byte();
		*temp=((int)MSB<<8)+LSB;
	}
	EA=1;
	return ~ack;
}
