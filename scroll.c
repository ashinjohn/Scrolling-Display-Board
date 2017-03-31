#include<avr/io.h>
#define F_CPU 16000000UL // internal clock
#include <util/delay.h>

#include<avr/interrupt.h>
char chek[3]={'+','C','M','T'};
char mc[1]={'O','K'};

char mmn=48;
int luk=0;
volatile unsigned int O_flag=0,K_flag=0;
int i;
int wrong_number = 0;
char mynum[10]={'9','5','4','4','9','0','7','3','7','4'};

int norep = 0;

char O ='O';

int key=0;
int c1=0;
int startstor=0;
int nmre=0;
int po=0;
int mat=0;

void lcd_cmd1 (char cmd);
void lcd_data1 (char dat);
void lcd_cmd2 (char cmd);
void lcd_data2 (char dat);


char a[30]={'S','C','R','O','L','L','I','N','G',' ','D','I','S','P','L','A','Y','.'};

void scroll(char arr[])
{
	lcd_cmd1(0x01);
	lcd_cmd2(0x01);
	lcd_cmd1(0x80);
	lcd_cmd2(0x80); 
 
 int b=0;
while (1)
{
 
 for (b=0;b<32;b++) // to circle main
 {
 
 	for (int c=0;c<=b;c++)
	{ 
	if (b<15) 
	lcd_data1(' ');    //space boy
	else
	lcd_data2(' ');
	}

   for (int d=0;arr[d]!='.';d++)
	{
	if (d<15-b) 
	lcd_data1(arr[d]);    //matter
	else
	lcd_data2(arr[d]);
	}


 	lcd_cmd1(0x01);
	lcd_cmd2(0x01);
	lcd_cmd1(0x80);
	lcd_cmd2(0x80); 

if (b>30)
	b=0;
 
 
 
 } //for loop main circle 

} //whole while group
} // scroll


#include<string.h>
volatile unsigned char stor[100];
volatile unsigned char numsor[100];
volatile unsigned char value;
int len=0;
int kin=0;
int s1=0;

void prints(char *ptr)
{
while(*ptr)
{
send_char(*ptr);
ptr++;
}
}



ISR(USART_RXC_vect) // used to give location of interuppt
    {
	
	


	value = UDR;	// data comes by the name UDR

	
	
	if(value=='O')
	O_flag=1;

	else if((value=='K')&&(O_flag==1))
	{
	K_flag=1;
	O_flag=0;
	}


    
	
		if (value==chek[c1]&& nmre==0)
		{
		c1++ ;
		key++;
	
		}
		else { c1=0; key=0;  }
	 
	 if (key >2)
	{	 startstor = 1;   nmre=1;  }
	 
	
   if (startstor==1)
   {
     if (po<18&&po>7)//>7
  { 
   numsor[kin]= value; 
//  send_char(value);
   kin++;
   
   
   }

  
   	if (po>40&&po<57)
   { 
   stor[len]= value; 
 send_char(value);   // Print content of text SMS

   len++;
   mmn++;
   
   }
   
   
po++;

 
 		 if (len>15)   //15
 {

//   	lcd_cmd(0x80);
	for(i=0;i<=9;i++)
   {
 //   lcd_data(numsor[i]);
	if(numsor[i]!=mynum[i])
	{
	wrong_number=1;
 	break;
	}
	}   
//lcd_cmd(0xC0);
//    lcd_data(stor[12]); 
 //   lcd_data(stor[15]); 


	wrong_number=0;

   
   
   



	
  				for(po=0;po<100;po++)
 			  stor[po]=' ';

			

		 	for(po=0;po<100;po++)
  			 numsor[po]=' ';

		 key=0;
	 	c1=0;
 		 startstor=0;
	 	nmre=0;
		 po=0;
		len=0;
		kin=0;
		 
		 
		 
		 }
  


	}

}
   

//	UCSRA = 0x40;    // 0100 0000 bit format when data completly transferred 
	

//	UDR = value+1;   // a => b 
//	while((UCSRA&0x40)==0); // checks whether data tranferring has been completed
							// (UCSRA&0x40) will be 0 until data transfer comletes !
							// jump out when it is not zero
	
	

void send_char (volatile unsigned char c ) 
	{
	UCSRA = 0x40;
	UDR=c;					//giving data input to UDR
	while ((UCSRA&0x40)==0); // check for transmission complete
	}


int main (void)
{

/* ********* lcd 1 init ************************************** */

DDRC = 0xFF;  //data
DDRD = 0xE0;  // command 


lcd_cmd1(0x30);  // one line
lcd_cmd1(0x30);  
lcd_cmd1(0x38);  // just this two line required
lcd_cmd1(0x06);  // auto addressing
lcd_cmd1(0x0C);  // cursor off
lcd_cmd1(0x01);  // clear display
lcd_cmd1(0x80);  // first row first location
//lcd_cmd1(0xE0);  // second row first location


/* **************** lcd 2 init ****************************** */

DDRA = 0xFF;  //data
DDRB = 0xE0;  // command 


lcd_cmd2(0x30);  // one line
lcd_cmd2(0x30);  
lcd_cmd2(0x38);  // just this two line required
lcd_cmd2(0x06);  // auto addressing
lcd_cmd2(0x0C);  // cursor off
lcd_cmd2(0x01);  // clear display
lcd_cmd2(0x80);  // first row first location
//lcd_cmd2(0xE0);  // second row first location

// ****************************************************************






DDRB = 0xFF;  //seting port as output 1111 1111

UBRRL = 0x67;// to set baud rate 104

 UBRRH = 0x00;// to set high bit 00   */

 //UCSRA=UCSRB=UCSRC=0x00;
 
 UCSRB=0x98; 
 UCSRC=0x86; //usart control & status registter c enable

 
 sei();    // global interrupt enable



lcd_data1('A');
lcd_data2('s');

scroll(a);




/*
while(K_flag==0)
{
prints("AT\r\n");
//lcd_data('.');
_delay_ms(2000);
}

prints("ATE0\r\n");


prints("AT+IPR=9600\r\n");


prints("AT+CMGF=1\r\n");


prints("AT+CNMI=1,2,0,0,0\r\n"); // respond to incomming message




sei();

*/

 while(1);

 } //main


// ********lcd 1 setup****************************************	
void lcd_cmd1 (char cmd) // deals with command register
{
PORTD &=(~0x80); // setting RS 0 for command register
PORTD &=(~0x40); // X0XX XXXX  setting ~write
PORTC = cmd;
PORTD |= 0x20; 		// enable high
PORTD &= (~0x20);	// enable low
_delay_ms(10);		// delay for slow device



}

void lcd_data1 (char dat)  // Data Register
{
PORTD |= 0x80;    // high RS for data reg
PORTD &= (~0x40); // low as writing onto lcd screen 
PORTC= dat;
PORTD |= 0x20;	
PORTD &= (~0x20); // enable routine

_delay_ms(10);

}


// ********lcd 2 setup****************************************	

void lcd_cmd2 (char cmd) // deals with command register
{
PORTB &=(~0x80); // setting RS 0 for command register
PORTB &=(~0x40); // X0XX XXXX  setting ~write
PORTA = cmd;
PORTB |= 0x20; 		// enable high
PORTB &= (~0x20);	// enable low
_delay_ms(10);		// delay for slow device

}

void lcd_data2 (char dat)  // Data Register
{
PORTB |= 0x80;    // high RS for data reg
PORTB &= (~0x40); // low as writing onto lcd screen 
PORTA= dat;
PORTB |= 0x20;	
PORTB &= (~0x20); // enable routine

_delay_ms(10);

}

//*************************************************************


