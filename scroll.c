#include<avr/io.h>
#define F_CPU 16000000UL // internal clock
#include <util/delay.h>

#include<avr/interrupt.h>


#define LED_DIR		(DDRB |= _BV(PORTB3))    //set LED port as output port 
#define LED_ON		(PORTB |= _BV(PORTB3))   //switch ON LED
#define LED_OFF		(PORTB &= ~_BV(PORTB3))  //switch OFF LED

#define BUZ_DIR		(DDRB |= _BV(PORTB2))    //set buzzer port as output port 
#define BUZ_ON		(PORTB |= _BV(PORTB2))   //switch ON buzzer
#define BUZ_OFF		(PORTB &= ~_BV(PORTB2))  //switch OFF buzzer

int t;
int zz;

char s9[]={"CONNECTING MODEM"};

char s6[]={"LINK STABLE"};
char s7[]={"MESSAGE DISPLAY"};
char s8[]={" DEVICE READY"};
char su[]={" UNKNOWN NUMBER"};


//   new data

int stop=0;



void lcd_cmd1 (char cmd);
void lcd_data1 (char dat);
void lcd_cmd2 (char cmd);
void lcd_data2 (char dat);


void scroll(volatile unsigned char a[])
{
	
	LED_ON;
	BUZ_ON;
	_delay_ms(500);
	BUZ_OFF;
	LED_OFF;
		

	


	lcd_cmd1(0x01);
	lcd_cmd2(0x01);
	lcd_cmd1(0x80);
	lcd_cmd2(0x80); 
 
 int b=0;
volatile unsigned char arr[40];
int zz,z;

for(z=15,zz=0;a[z]!='*';zz++,z++)
	arr[zz]=a[z];

	arr[zz]='*';




while (1)
{
 start:	lcd_cmd1(0x01);
	lcd_cmd2(0x01);
	lcd_cmd1(0x80);
	lcd_cmd2(0x80); 
 for (b=0;b<32;b++) // to circle main
 {
 
 		for (int c=0;c<=b;c++)
		{ 
		if (b<15) 
		lcd_data1(' ');    //space boy
		else
		lcd_data2(' ');
		}

  	 	for (int d=0;arr[d]!='*';d++)
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
	{
		lcd_cmd1(0x01);
		lcd_cmd2(0x01);
		lcd_cmd1(0xC0);
		lcd_cmd2(0xC0);



		for (b=0;b<32;b++) // to circle main
 	 	{
 
	
			for (int c=0;c<=b;c++)
			{ 
			if (b<15) 
			{
			lcd_data1(' ');    //space boy
		//	_delay_ms(100);
			}
			else
			{
			lcd_data2(' ');
		//	_delay_ms(100);
			}
			}

   			for (int d=0;arr[d]!='*';d++)
			{
			if (d<15-b) 
			{
			lcd_data1(arr[d]);    //matter
		//	_delay_ms(100);
			}
			else
			{
			lcd_data2(arr[d]);
		//	_delay_ms(100);
			}
	
			} //for
		
		if (b>30)
		 { b=0;   break;  }
	
	
	 	lcd_cmd1(0x01);
		lcd_cmd2(0x01);
		lcd_cmd1(0xC0);
		lcd_cmd2(0xC0);

		}

	} //b>30
 
 
 
 
 
 } //for loop main circle 

} //whole while group
} 

 // *************


int fail=0;
int has=0;
int was=0;	
	

char pass[10]={'P','A','S','S','W','O','R','D'};

char chek[3]={'+','C','M','T'};
char mc[1]={'O','K'};


char mmn=48;
int luk=0;
volatile unsigned int O_flag=0,K_flag=0;
int i;
int wrong_number = 0;
char mynum[10]={'9','4','9','7','7','0','7','1','5','0'};
//sujithnum {'9','4','9','7','7','0','7','1','5','0'};

int norep = 0;

char O ='O';

int key=0;
int c1=0;
int startstor=0;
int nmre=0;
int po=0;
int mat=0;

void lcd_cmd2 (char cmd);
void lcd_data2 (char dat);



#include<string.h>
volatile unsigned char stor[100];
volatile unsigned char numsor[100];

volatile unsigned char bank[100];
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
	
		}																						`		
		else { c1=0; key=0;  }
	 
	 if (key >2)
	{	 startstor = 1;   nmre=1;  }
	 
	
   if (startstor==1)
   {
    	 if (po<18&&po>7)//>7
	  	 { 
   		  numsor[kin]= value; 

  		 kin++;
		 }

		if (po>40&&stop==0)// gsm 40 57
   		{ 
 		stor[len]= value; 

   		len++;
  		 mmn++;
   
  		 if (value=='.')
 		{
		stop=1;
		} 
  
  
   }
   
   
po++;

 
 		 if (stop==1)   //gsm 15  27
 {
	lcd_cmd2(0x01);
   lcd_cmd2(0x80);
	
	
	for ( int queen =0 ;queen<10; queen++)
	   lcd_data2(numsor[queen]);

		_delay_ms(1000);
	
	
	for(i=0;i<=9;i++)
   {
 		if(numsor[i]!=mynum[i])
		{
		wrong_number=1;
 	
	     	lcd_cmd2(0xC0);
				for (t=0;t<strlen(su);t++)
			{
			 lcd_data2(su[t]);  // unknown number
			}

		break;
		}
	} 
	  
lcd_cmd2(0xC0);
 
 	
// WHERE THINGS HAPPEN


int boss;



int kid;
int k;

int sea;

// startng location ... p.. 6

/*

for(sea=6;sea<6+8;sea++)
{	
	lcd_data2(stor[sea]);
	
	//if (stor[sea]=='*')
	//while(1);
}


*/




	for(kid=6,k=0;kid<6+8;kid++,k++)
	{


 		if(stor[kid]!=pass[k])
 		{ 
 		fail=1;
 
 			char SHOW1[]={" NEED SHIFTING"};
 			char SHOW2[]={" WRONG PASSWORD"};

			lcd_cmd2(0x01);  // clear display
			lcd_cmd2(0x80);  // first row first location



			for (t=0;t<strlen(SHOW1);t++)
				{
	// 	lcd_data(SHOW1[t]);  // SHIFTING
				}


				lcd_cmd2(0xC0);

				for (t=0;t<strlen(SHOW2);t++)
				{
				lcd_data2(SHOW2[t]);  // WRONG PASSWPRD
				}
				while(1);

	break; 
 		} // stor kid clsoing



	} //kid closing

	
//	for (boss=14;boss!=was&&fail==0;boss++ )



/*	for (boss=15;fail==0;boss++ )
	{
	lcd_data2(stor[boss]);

	if (stor[boss]=='*')
	break;
	} */

key=0;
	 	c1=0;
 		 startstor=0;
	 	nmre=0;
		 po=0;
		len=0;
		kin=0;
		
		stop=0;
		

for(po=0;po<100;po++)
  	numsor[po]=' ';


 
if(wrong_number!=1&&fail==0)
{
  wrong_number=0;
  fail=0;

for(po=0;po<100;po++)
 	bank[po]= stor[po]; 

for(po=0;po<100;po++)
 	stor[po]=' ';



	 
scroll(bank);
}	  
   
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
		fail=0;
		stop=0;
		wrong_number=0;
	
		 
		 
		 
	
  


	}


UCSRA=0x40;
	UDR=value;
	while((UCSRA&0x40)==0);


 
}
} //vector closing
   



void send_char (volatile unsigned char c ) 
	{
	UCSRA = 0x40;
	UDR=c;					//giving data input to UDR
	while ((UCSRA&0x40)==0); // check for transmission complete
	}


int main (void)
{


LED_DIR;
BUZ_DIR;

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


lcd_cmd2(0x01);	
lcd_cmd2(0x80);
for (t=0;t<strlen(s7);t++)
{
lcd_data2(s7[t]);  // data to show on lcd
}

	_delay_ms(1000);

lcd_cmd2(0x01);	
lcd_cmd2(0x80);




int king;







lcd_cmd2(0x01);	
lcd_cmd2(0x80);




_delay_ms(100);

//DDRB = 0xFF;  //seting port as output 1111 1111

UBRRL = 0x67;// to set baud rate 104

 UBRRH = 0x00;// to set high bit 00   */

 //UCSRA=UCSRB=UCSRC=0x00;
 
 UCSRB=0x98; 
 UCSRC=0x86; //usart control & status registter c enable

 
 sei();    // global interrupt enable

	lcd_cmd2(0xC0);
for (t=0;t<strlen(s8);t++)
{
lcd_data2(s8[t]);  // data to show on lcd
}


_delay_ms(1000);
lcd_cmd2(0x01);


	lcd_cmd2(0x80);
for (t=0;t<strlen(s9);t++)
{
lcd_data2(s9[t]);  // data to show on lcd
}

while(K_flag==0)
{
prints("AT\r\n");
//lcd_data2('.');
_delay_ms(2000);
}


prints("ATE0\r\n");

//_delay_ms(2000);
prints("AT+IPR=9600\r\n");

//_delay_ms(2000);
prints("AT+CMGF=1\r\n");
//_delay_ms(2000);

prints("AT+CNMI=1,2,0,0,0\r\n"); // respond to incomming message
//_delay_ms(2000);

	lcd_cmd2(0xC0);
for (t=0;t<strlen(s6);t++)
{
lcd_data2(s6[t]);  // data to show on lcd
}

sei();


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

