
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 	
#include <sys/ioctl.h> 	
#include <termios.h> 
#include "GPIO_D.h"
#include <wiringPi.h>
#include <wiringSerial.h>

#define RET_MIN 1	
#define RET_MAX 2100
#define PASO_MIN 1	
#define PASO_MAX 10	
#define CAM_PASO	50
#define DECLARAR_SALIDAS { for( i = 0 ; i < VEC_SIZE ; i++	)	pinMode_D( sal[i], OUTPUT); }
#define APAGAR_LEDS {for( i = 0 ; i < VEC_SIZE ; i++	) digitalWrite_D(sal[i], LOW);}
#define QUIT 27
#define VEC_SIZE 8

int sal[]={26, 21, 20, 16, 12, 25, 24, 23};	

int InitUart(void); 
void secuencia1(unsigned char );
int leer_int(void); 
int map (int val);
int tab_dat(int estados, char sec[], int retardo); 
 
void secuencia2(unsigned char );
void secuencia3(unsigned char );
void secuencia4(unsigned char );
void secuencia5(unsigned char );
void secuencia6(unsigned char );
void secuencia7(unsigned char );
void secuencia8(unsigned char );

int puerto_serie;

int main(void)
{
	int sec;
	char char_sec;
	char ACK = 1;
	unsigned char velocidad = 0; 
	
	system("clear");
	InitUart();
	

	
	
	while(1)
	{
		sec=0;
		char_sec=0;
		
		do
		{
				read(puerto_serie, &char_sec, 1); 
				sec = (int) (char_sec - 48);		
		
		}while(sec < 1 || sec > 8)	;
		
		printf("SECUENCIA = %d	;	", sec);
				 
		write (puerto_serie, &ACK ,1);
		
		velocidad = 0; 
		do
		{
				read(puerto_serie, &velocidad, 1); 
									
		}while (velocidad == 0 );
		
		printf("VELOCIDAD = %d\n", velocidad);
		
		write (puerto_serie, &ACK ,1);
					
		switch (sec) 
		{
			case 0 : break;				
			case 1 : { secuencia1(velocidad); break; }
			case 2 : { secuencia2(velocidad); break; }
			case 3 : { secuencia3(velocidad); break; } 
			case 4 : { secuencia4(velocidad); break; }
			case 5 : { secuencia5(velocidad); break; }
			case 6 : { secuencia6(velocidad); break; }
			case 7 : { secuencia7(velocidad); break; } 
			case 8 : { secuencia8(velocidad); break; }
		}
			 
			
	}
  	
	return 0;
}


void secuencia1(unsigned char velocidad) 
{	
	int i,j;		
	int der=1; 
	int aux; 
	int retardo= 0; 

	pioInit();					
		
	DECLARAR_SALIDAS
	
	i = 0;	
	retardo = map((int)velocidad);
	
	do{
		
		
		digitalWrite_D(sal[i], HIGH);	
		
		for( j=0 ; j < retardo ; j++)
		{		
			delay(1);
			
			read(puerto_serie, &velocidad, 1);
			
			if( velocidad == 0 )
				break;
			
			retardo = map((int)velocidad);
							
		}	
		
		digitalWrite_D(sal[i], LOW);		
		
		
		if(der)			
			i++;
		else			
			i--;
		
		if(i == VEC_SIZE-1)	
			der = 0;
		
		if(i == 0)		
			der = 1;
							
	 }while( velocidad != 0); 
	
		
	APAGAR_LEDS	
			
}

void secuencia2(unsigned char velocidad) 
{

   char secuencia[] = {0b10000000, 0b10000000, 0b01000000, 0b01000000, 0b00100000, 0b00100000, 0b10010000, 0b01010000, 0b00101000, 0b00011000, 0b00001100, 0b00000100, 0b00000010 ,0b00000010, 0};
   int i;
   int retardo= 0;
  
  
    
 	pioInit();			
	
		
		
	DECLARAR_SALIDAS
	
	
	
	i = 0;			
	
	retardo = map((int)velocidad);
	
  tab_dat ( (int) strlen(secuencia), secuencia, retardo) ; 

	APAGAR_LEDS
		

}



int map(int val) 
{
	if(val > 206 ) 
		return ( 256-val); 
	else if (val <= 206) 
		return ( ((206-val)*10) + CAM_PASO); 
		
}



int tab_dat(int estados, char sec[], int retardo) 
{
	
	char aux = 0b10000000;
	int velocidad=0;
	int i, j;
		
	do
	{
			for(j=0 ; j<estados ; j++)
			{		
				for(i=0 ; i<8 ; i++) 
				{
					if (sec[j] & aux >> i)
						digitalWrite_D(sal[i], HIGH); 
					else 
						digitalWrite_D(sal[i], LOW);
				}
				
				for(i=0; i < retardo ; i++) 
				{
					delay(1);	
					
					read(puerto_serie, &velocidad, 1);
			
					if( velocidad == 0 )
						return 0;
			
					retardo = map((int)velocidad);
				}
				
			}
			
	}while(1);
			
								
}

void secuencia3 (unsigned char velocidad ) 
{
  
  
  int i,j;		
  int ch;	
  int tope=7;
  int retardo=0; 
  
 
	retardo = map((int)velocidad);	
	pioInit();					
	DECLARAR_SALIDAS
	
	i = 0;			
	 	
	do{
	
			
			digitalWrite_D(sal[i], HIGH);		
			
			for(j = 0 ; j < retardo ; j++) 
			{
				delay(1);
				read(puerto_serie, &velocidad, 1);
				if( velocidad == 0 )
					break;		
				retardo = map((int)velocidad);	
			} 
			
			
			digitalWrite_D(sal[i], LOW);		
							
			if(i == tope)				
			{
					for(j = 0 ; j < 50 ; j++) 
				{
					delay(1);
					
					read(puerto_serie, &velocidad, 1);
					if( velocidad == 0 )
						break;		
					
					retardo = map((int)velocidad);	
			
				} 
				digitalWrite_D(sal[i], HIGH);	
					
					for(j = 0 ; j < 50 ; j++) 
				{
						delay(1);
						read(puerto_serie, &velocidad, 1);
						if( velocidad == 0 )
							break;		
							
						retardo = map((int)velocidad);	
				} 				
							
				tope--;						
				i=0;						
			}
			else
				i++;	
		
			if(tope == -1)	
			{
				APAGAR_LEDS
				i = 0;
				tope = 7;
			}
			
	
				
	}while( velocidad != 0); 
		
	APAGAR_LEDS

}


void secuencia4 (unsigned char velocidad) 
{
  int i,j;		
  int retardo;
  	
	pioInit();					
		
	DECLARAR_SALIDAS
				
	i = 0;			
	retardo = map((int)velocidad);
	
	do{
					
			digitalWrite_D(sal[i], HIGH);		
			digitalWrite_D(sal[ VEC_SIZE-1-i ], HIGH);
			
			for(j=0 ; j < retardo ; j++) 
			{
						delay(1);
						
						read(puerto_serie, &velocidad, 1);
			
						if( velocidad == 0 )
							break;
			
						retardo = map((int)velocidad);
						
			}
						
			digitalWrite_D(sal[i], LOW);
			digitalWrite_D(sal[ VEC_SIZE-1-i ], LOW);
		
			i++;
		
			if( i == 4 )		
				i = 5;
	
			if(i == VEC_SIZE)
				i = 1;
			
			
	
	}while( velocidad != 0 ); 
	
APAGAR_LEDS
  
}

void secuencia5(unsigned char velocidad) 
{

   
   unsigned char secuencia[256] = {0};
   int i;
   int retardo = 0;
   
	pioInit();			
		
  DECLARAR_SALIDAS

  for(i=0; i < 256 ; i++)
    secuencia[i] = i; 
	
	i = 0;			
	
	retardo = map((int)velocidad);
		
  tab_dat ( 256, secuencia, retardo) ; 

 APAGAR_LEDS
}

void secuencia6 (unsigned char velocidad)
{
	
	char secuencia[] = {0b11000000, 0b00000011, 0b00110000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000 ,0b00100000, 0b01000000, 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b11111111, 0};
   int i;
   int retardo = 0;
   
	pioInit();			
		
	DECLARAR_SALIDAS
				
	i = 0;			
	
	retardo = map((int)velocidad);
	
  tab_dat ( (int) strlen(secuencia), secuencia, retardo) ; 

  APAGAR_LEDS

}

void secuencia7 (unsigned char velocidad) 
{
  
  int i,j;		
  int retardo=0;
     	
	pioInit();					
		
  DECLARAR_SALIDAS
				
	i = 3;	
	retardo = map((int)velocidad);		
		
	do{	   
      digitalWrite_D( sal[i], !digitalRead_D(sal[i]) );
      digitalWrite_D( sal[VEC_SIZE -1 -i], !digitalRead_D( sal[VEC_SIZE -1 -i]) );
      i--; 
      for(j=0 ; j < retardo ; j++)
        {
            delay(1);
												
						read(puerto_serie, &velocidad, 1);
			
						if( velocidad == 0 )
							break;
			
						retardo = map((int)velocidad);
        }
			
	  if(i == -1) 
      i = 3; 

	}while( velocidad != 0); 
	
APAGAR_LEDS
  
}

void secuencia8 (unsigned char velocidad) 
{
  
  int i,j;		
  int retardo=0;
  int apagar = 1;
    	
	pioInit();					
		
  DECLARAR_SALIDAS
				
	i = 0;			
	retardo = map((int)velocidad);
	
	do{	     
      digitalWrite_D( sal[i], HIGH );
      			
      for(j=0 ; j < retardo ; j++)
        {
            delay(1);
            read(puerto_serie, &velocidad, 1);
			
						if( velocidad == 0 )
							break;
			
						retardo = map((int)velocidad);
						
        }
			
	  if( apagar ) 
      digitalWrite_D( sal[i], LOW);
      
     
    if( i == 6 ) 
			 i = 1;
			 
		else if( i == 7)
		{
			if( !apagar )
			{
					delay(30);
					
					APAGAR_LEDS
						
					delay(30);	
			}
			
			apagar = !apagar;
			i = 0;
		}	 	
    
    else
       i += 2;
   
	}while( velocidad != 0) ; 
	
	APAGAR_LEDS
}
