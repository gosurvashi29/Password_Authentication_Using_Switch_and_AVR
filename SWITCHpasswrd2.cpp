# define F_CPU 1000000
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num,int m);
void disp_string(  char *str);
void disp_password();

int b[3];

int main(void)
{
	DDRA=0X00;
	DDRB=0XFF;
	PORTA=0XFF;
	DDRC = 0XFF;
int m=0;
	lcd_init();

	while (1)
	{
		
		disp_cmd(0X80);
		disp_string("WELCOME");
		_delay_ms(100);
		disp_cmd(0X01);
		_delay_ms(2);
		disp_cmd(0X80);
		disp_string("Enter the paswrd");
		
		
		if (PINA==0b11111110)
		{
			PORTB=0b00000001;//1
			disp_cmd(0XC0);
			disp_num(1,m);
			m++;
			
		}
		
		else if (PINA==0b11111101)
		{
			PORTB=0b00000010;//2
			disp_cmd(0XC1);
			disp_num(2,m);
			m++;
		}
		else if (PINA==0b11111011)
		{
			PORTB=0b00000100;//3
			disp_cmd(0XC2);
			disp_num(3,m);
		m++;
		}
		
		else if (PINA==0b11110111)
		{
			PORTB=0b00001000;//4
			disp_cmd(0XC3);
			disp_num(4,m);
			m++;
		}
		else if (PINA==0b11101111)
		{
			PORTB=0b00010000;//5
			disp_cmd(0XC4);
			disp_num(5,m);
			m++;
		}
		else if (PINA==0b11011111)
		{
			PORTB=0b00100000;//6
			disp_cmd(0XC5);
			disp_num(6,m);
			m++;
		}
		else if (PINA==0b10111111)
		{
			PORTB=0b01000000;//7
			disp_cmd(0XC6);
			disp_num(7,m);
			m++;
		}
		else if (PINA==0b01111111)
		{
			disp_password();
		}
	}
	return 0;
}

void disp_cmd(unsigned int cmd)
{
	PORTC=((cmd & 0XF0)+0X04);
	_delay_ms(1);
	PORTC=PORTC - 0X04;
	PORTC=(((cmd<<4)& 0XF0)+0X04);
	_delay_ms(1);
	PORTC=PORTC-0X04;
	
}
void disp_data( int cmd)
{
	PORTC=((cmd  & 0XF0)+0X05);
	_delay_ms(1);
	PORTC=PORTC - 0X04;
	PORTC=(((cmd <<4)& 0XF0)+0X05);
	_delay_ms(1);
	PORTC=PORTC-0X04;
	
}

void disp_string( char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		disp_data (str[i]);
		i++;
		
	}
}

void disp_num(unsigned int num,int m)
{
	int  a=0;
	
	
	
	
	
	if (num==0)
	{
		disp_data(48);
		b[m]=num;
		
	}
	disp_cmd (0X04);
	while (num!=0)
	{
		b[m]=num;
		a=num % 10;
		disp_data(a+48);
		num=num/10;
		
	}
	
	
}
void disp_password()
{
	int c, m,n,d[3], pswrd=1234;		
	for (n=3;n>=0;n--)
	{
	
		c=pswrd % 10;
		d[n]=c;
		pswrd=pswrd/10;
	}	
		
	for (m=0;m<=3;m++)
	{
		for (n=0 ;n<=3;n++)
		{
			if (b[m]!=d[n])
			{
				disp_cmd(0XC0);
				disp_string("password not match");
				goto start;
			}				
			}
		}
		
		disp_cmd(0XC0);
		disp_string("passwrd matched");
	
		
	
		 
	
	start:
	disp_cmd(0X06);
		
}
void lcd_init()
{
	disp_cmd(0X02);
	disp_cmd(0X28);
	disp_cmd(0X0C);
	disp_cmd(0X06);
}