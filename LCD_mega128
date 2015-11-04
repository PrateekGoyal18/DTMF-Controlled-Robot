/* LCD Header */
#include<avr/io.h>

#define CHECKBIT(x,b) (x&(1<<b))		//Checks bit status
#define SETBIT(x,b) x|=(1<<b)		//Sets the particular bit
#define CLEARBIT(x,b) x&=~(1<<b);		//Sets the particular bit
#define TOGGLEBIT(x,b) x^=(1<<b);		//Toggles the particular bit

#define LINE1	0x80
#define LINE2	0xC0

#define PORTUSED PORTA
#define DDRUSED DDRA

unsigned char k=0,j=0;
unsigned char save=0;

void delay_us(unsigned int tim);
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void toggleE(void);
void lcd_char(unsigned char single);
void lcd_string(unsigned char str[32]);
void lcd_showvalue(unsigned char num);
void lcd_gotoxy1(unsigned char pos);
void lcd_gotoxy2(unsigned char pos);
void lcd_exit(void);
void WaitMs(unsigned int ms);

void delay_us(unsigned int time)
{
	for(j=0;j<time;j++)
	{
		for(k=0;k<10;k++)
		{};
	}
}

void toggleE(void)
{
//WaitMs(1);
delay_us(100);
SETBIT(PORTUSED,2);
//WaitMs(1);
delay_us(100);
CLEARBIT(PORTUSED,2);
}

void lcd_cmd(unsigned char cmd)
{
	CLEARBIT(PORTUSED,0+2); // RS to 0 means select COmmand register, E to 0 ..
	PORTUSED=(cmd&0xF0)|(PORTUSED&(1<<3));			
	toggleE();
	PORTUSED=((cmd&(0x0F))*16)|(PORTUSED&(1<<3));	
	toggleE();
}

void lcd_init(void)	//init the lcd 
{	
	save=PORTUSED;
	DDRUSED=0xFF;		// declare it as an o/p port
	WaitMs(15);		// Given in datasheet ( Cmd for selecting 4 bit mode )
	lcd_cmd(0x03);
	WaitMs(45);
	lcd_cmd(0x02);
	WaitMs(15);
	CLEARBIT(PORTUSED,0+2);   // RS to 0 means select COmmand register, E to 0 ..
	//lcd_cmd(0x01);     // Cmd for clear display
	lcd_cmd(0x0F);		// Cmd for display ON and cursor blinking
	lcd_cmd(0x02);		// Cmd for returning home
	lcd_cmd(LINE1);		// selects the cursor to first line first location...
	WaitMs(15);			
}

void lcd_putchar(unsigned char sig)
{
	PORTUSED=(sig&0xF0)|(PORTUSED&(1<<3));						
	SETBIT(PORTA,0);		// selects dat register RS=1
	toggleE();
	PORTUSED=((sig&(0x0F))*16)|(PORTUSED&(1<<3));
	SETBIT(PORTA,0);		// selects dat register RS=1
	toggleE();
}

void lcd_char(unsigned char single)
{
	int i;
	if(single =='\t')
	{
		for(i =0 ; i<2 ; i++)
		{	
		lcd_putchar(' ');
		}
	}
	else if(single=='\n')
	{
		lcd_gotoxy2(0);	
	}
	else 
	{
		lcd_putchar(single);
	}
}

void lcd_string(unsigned char str[64])
{
	unsigned char k=0;
	CLEARBIT(PORTUSED,2);
	while(str[k]!='\0')	//Till null character is encountered
		{
			
			PORTUSED=((str[k])&0xF0)|(PORTUSED&(1<<3));
			SETBIT(PORTA,0);			// selects dat register RS=1
			toggleE();
			PORTUSED=((str[k]&(0x0F))*16)|(PORTUSED&(1<<3));
			SETBIT(PORTA,0);			// selects dat register RS=1
			toggleE();
			k++;
		}
}


void lcd_showvalue(unsigned char num)	//prints the decimal 3digit value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
	lcd_char(H+0x30);
	lcd_char(T+0x30);
	lcd_char(O+0x30);
}

void lcd_gotoxy1(unsigned char pos)
{
	lcd_cmd(LINE1+pos);     // write pos=0 if u want to select 1st location
}

void lcd_gotoxy2(unsigned char pos)
{
	lcd_cmd(LINE2+pos);		 // write pos=0 if u want to select 1st location
}


void lcd_exit(void)
{
	PORTUSED=save;
}

/* waits (pauses) for ms milliseconds (assumes clock at 16MHz) */
void WaitMs(unsigned int ms)
{
	int i;

	while (ms-- > 0)
	{
		/* 16384 (16k) clock cycles for 1ms; each time through loop
		   is 5 cycles (for loop control + nop) */
		for (i = 0; i < 3276; ++i)
			asm("nop");
	}
}

