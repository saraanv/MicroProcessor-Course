#include <mega32.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>
//-----------------------------------------------------------------------
int seg_code[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int x,y,d,p;
char str[16];
//-----------------------------------------------------------------------
int key_pad(void)  
{
  PORTB.4=0;
  PORTB.5=1;
  PORTB.6=1;
  PORTB.7=1;    
  if(!PINB.0) return 10;
  if(!PINB.1) return 9;
  if(!PINB.2) return 8;
  if(!PINB.3) return 7;
   
  PORTB.4=1;
  PORTB.5=0;
  PORTB.6=1;
  PORTB.7=1;    
  if(!PINB.0) return 11;
  if(!PINB.1) return 6;
  if(!PINB.2) return 5;
  if(!PINB.3) return 4;
   
  PORTB.4=1;
  PORTB.5=1;
  PORTB.6=0;
  PORTB.7=1;    
  if(!PINB.0) return 12;
  if(!PINB.1) return 3;
  if(!PINB.2) return 2;
  if(!PINB.3) return 1;
  
  PORTB.4=1;
  PORTB.5=1;
  PORTB.6=1;
  PORTB.7=0;    
  if(!PINB.0) return 13;
  if(!PINB.1) return 14;
  if(!PINB.2) return 0;
  if(!PINB.3) return 15;
  
  return 20;
}
//-----------------------------------------------------------------------
void main(void)
{      
  DDRA=0xff;
  DDRB=0b11110000;
  PORTB=0b00001111;
  DDRC=0xff;      
  DDRD=0x7f;
  
  lcd_init(16);
  lcd_puts("Enter 2 Digit : ");
  
  do
    d=key_pad();    
  while(d==20);  
  lcd_putchar(d+48);
  
  delay_ms(300);
          
  do
    y=key_pad();    
  while(y==20);   
  lcd_putchar(y+48); 
  
  x=d*10+y;    
  delay_ms(950);
  
  while (1)
   {          
        if(PIND.7==0) p=1;
        else p=-1;
        
        y=x%10;
        d=x/10;
        PORTC=seg_code[y];
        PORTD=seg_code[d]; 
        
        sprintf(str,"%d",x);
        lcd_clear();
        lcd_puts(str);
        
        delay_ms(950);
        
        x+=p;  
        if(x>99) x=0;
        if(x<0) x=99;        
   } 
      
}
