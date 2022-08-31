# define F_CPU 1000000
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);
int disp_key();
int main(void)
{
	DDRA=0X00;
	DDRB=0XFF;
	PORTA=0XFF;
	DDRC = 0XFF;

	lcd_init();
	int y=0,k=0;
	disp_cmd(0X80);
	disp_string("WELCOME");
	_delay_ms(1000);
	disp_cmd(0X01);
	_delay_ms(2);
	disp_cmd(0X80);
	disp_string("Enter the paswrd");
	
	while (1)
	{
		
		while(k!=8)
		{
			int k=disp_key();
			if (k==8)
			{
				break;
			}
		
		else
		{
			y=(y * 10+k);
			disp_cmd(0XC4);
			disp_num(y);
		}
		}					
				if (y==1234)
				{
					disp_cmd(0X01);
					_delay_ms(2);
					disp_cmd(0X80);
					disp_string( "PASSWORD MATCHED");
					
					
				}
				else{
					disp_cmd(0X01);
					_delay_ms(2);
					disp_cmd(0X80);
					disp_string( "PASSWORD NOT MATCHED");
					
					
				}
			}
			
		
			
		return 0;
	}
	int disp_key()
	{
		while (1)
		{
			
			if (PINA==0b11111110)
			{
				while (PINA==0XFE);
				
				
				PORTB=0b00000001;//1
				
				return 1;
				
				
			}
			
			else if (PINA==0b11111101)
			{
				while (PINA==0XFD);
				PORTB=0b00000010;//2
		
				return 2;
			}
			else if (PINA==0b11111011)
			{
				while (PINA==0XFB);
				PORTB=0b00000100;//3
				
				return 3;
			}
			else if (PINA==0b11110111)
			{
				while (PINA==0XF7);
				PORTB=0b00001000;//4
				
				return 4;
			}
			else if (PINA==0b11101111)
			{
				while (PINA==0XEF);
				PORTB=0b00010000;//5
			
				return 5;
			}
			else if (PINA==0b11011111)
			{
				while (PINA==0XDF);
				PORTB=0b00100000;//6
			
				return 6;
			}
			else if (PINA==0b10111111)
			{
				while (PINA==0XBF);
				PORTB=0b01000000;//7
			
				return 7;
			}
			else if (PINA==0b01111111)
			{
				while (PINA==0X7F);
				PORTB=0b10000000;//8
			
				return 8;
			}
		
			
		}
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

	void disp_num(unsigned int num)
	{
		int a=0;
		if (num==0)
		{
			disp_data(48);
		}
		disp_cmd (0X04);
		while (num!=0)
		{
			a=num % 10;
			disp_data(a+48);
			num=num/10;
		}
	}
	void lcd_init()
	{
		disp_cmd(0X02);
		disp_cmd(0X28);
		disp_cmd(0X0C);
		disp_cmd(0X06);
	}	