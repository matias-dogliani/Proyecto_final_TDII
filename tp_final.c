


#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "TP_FINAL.h"
#include "GPIO_D.h"
#include <ncurses.h>	


#define VEC_SIZE 8
#define RET_MIN 1		
#define RET_MAX 2100	
#define PASO_MIN 1		
#define PASO_MAX 10		
#define CAM_PASO 50	
#define ENTER {printf("%c %c", 10,13);}
#define INIT_KEYBOARD  {filter(); initscr(); cbreak();	noecho(); nodelay(stdscr, TRUE);	keypad(stdscr, TRUE);	}
#define STOP_KEYBOARD {endwin();}
#define MODIFICAR_VELOCIDAD { if( ch == KEY_UP && retardo > RET_MIN) if( retardo > CAM_PASO ) retardo -= PASO_MAX; else	retardo -= PASO_MIN; if( ch == KEY_DOWN && retardo < RET_MAX) if( retardo > CAM_PASO )retardo += PASO_MAX;else retardo += PASO_MIN; }

#define DECLARAR_SALIDAS { for( i = 0 ; i < VEC_SIZE ; i++	)	pinMode_D( sal[i], OUTPUT); }
#define APAGAR_LEDS {for( i = 0 ; i < VEC_SIZE ; i++	) digitalWrite_D(sal[i], LOW);}
					
					

void est_vel(int sec);

int sal[]={26, 21, 20, 16, 12, 25, 24, 23};	

int retardo_1 = -100; 		
int retardo_2 = -100;
int retardo_3 = -100;
int retardo_4 = -100;
int retardo_5 = -100;
int retardo_6 = -100;
int retardo_7 = -100;
int retardo_8 = -100;

int main (void){
			
 if( ing_pwd() )
	while(1)
	{
		if( !menu() )
		return 0;
	}
  else 
      return 0; 
	
}


int menu (void){
 
  int op = 0;
  int i; 

	

 do{
	 system("clear");
	printf("Menú principal: \n\n");
	printf("1  - Secuencia \"Auto fantástico\".\n");
	printf("2  - Secuencia \"La carrera\".\n");
	printf("3  - Secuencia \"La Apilada \".\n");
	printf("4  - Secuencia \"El Choque \".\n");
	printf("5  - Secuencia personalizada 1.\n");
	printf("6  - Secuencia personalizada 2.\n");
	printf("7  - Secuencia personalizada 3.\n");
	printf("8  - Secuencia personalizada 4.\n");
	printf("9  - Establecer velocidad inicial de cada secuencia.\n");
	printf("10 - Control remoto.\n");
	printf("0  - Salir.\n\n");

	printf("Seleccione una opción: ");
	scanf("%d", &op);
	getchar();

	switch (op) 
	{
		case 0 : break;				
		case 1 : { secuencia1(); break; }
		case 2 : { secuencia2(); break; }
		case 3 : { secuencia3(); break; } 
		case 4 : { secuencia4(); break; }
		case 5 : { secuencia5(); break; }
		case 6 : { secuencia6(); break; }
		case 7 : { secuencia7(); break; } 
		case 8 : { secuencia8(); break; }
		case 9 : 
				{ 
					for(i=1; i<9; i++)
				   		est_vel(i);
					break; 
				}
				 
		case 10 : { control_remoto(); break;} 
		default: 
			 {   
				printf("\nOpción no valida, intente nuevamente.");
				getchar();	
			 }   
	}
  		 
   }while(op != 0);
   
return 0;
}



void est_vel(int sec)
{
	const char PCF8591 = 0x48;	

	int fd, val;
	char ch=0;	
	
	if (wiringPiSetup () == -1) 
		exit (1);	

	fd = wiringPiI2CSetup(PCF8591);		
  
	system("clear");
	printf("Estableciendo la velocidad inicial de la secuencia %d.\n", sec);
	printf("Presione ESC para salir. \n \n");
	printf("Velocidad actual = ");
	
	keyboard_start();

	system("setterm -cursor off");
	do{
		val = wiringPiI2CReadReg8(fd, PCF8591 ) ;	
		
		if ( val != -1)
		{
			printf("%03d", val);
			refrescar();
		
		} 
		
		read(0,&ch,1);
			  
    }while( ch != QUIT); 
	system("setterm -cursor on");
	keyboard_stop();
	
	map(sec, val);		
						
}



void secuencia1() 
{	
	int i,j;		
	int der=1; 
	int ch;			
	int retardo; 
	
	if( retardo_1 == -100)		
		est_vel(1);
		
	pioInit();					
		
	DECLARAR_SALIDAS

	i = 0;	
		
	INIT_KEYBOARD			
	system("clear");
	printf("Secuencia Auto fantástico.");
	ENTER 
	printf("Presione ESC para salir.");
	ENTER
	printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad. ");
	ENTER 
	ENTER
	printf("Velocidad actual = ");
	
	
	system("setterm -cursor off");
	
	do{
		
		
		digitalWrite_D(sal[i], HIGH);	
		
		for( j=0 ; j < retardo_1 ; j++)
		{		
		
			printf("%03d",rmap(retardo_1));
			refrescar();
			
			

			delay(1);
					
			ch = getch();		
			retardo = retardo_1;
			MODIFICAR_VELOCIDAD
			retardo_1=retardo;
			if(ch == QUIT) 	break;
			
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
		
		
		

				
	 }while( ch != QUIT); 
	
	system("setterm -cursor on");
	STOP_KEYBOARD							
	APAGAR_LEDS
	

}


void secuencia2() 
{
   char secuencia[] = {0b10000000, 0b10000000, 0b01000000, 0b01000000, 0b00100000, 0b00100000, 0b10010000, 0b01010000, 0b00101000, 0b00011000, 0b00001100, 0b00000100, 0b00000010 ,0b00000010, 0};
   int i;
   
   if( retardo_2 == -100)	
		est_vel(2);
	
	pioInit();			
		
	DECLARAR_SALIDAS
				
	i = 0;			
	
	INIT_KEYBOARD
	tab_dat ( (int) strlen(secuencia), secuencia, 2) ; 

	STOP_KEYBOARD

	APAGAR_LEDS
	
}

 void secuencia3 () 
{
  
 
  int i,j;		
  int ch;	
  int tope=7;
  int retardo=1; 
  
  if( retardo_3 == -100)		
		est_vel(3);
	
	pioInit();					
		
	DECLARAR_SALIDAS
				
	i = 0;			
	
	INIT_KEYBOARD
	system("clear");   				
	printf("Secuencia \"La apilada\".");
	ENTER
	printf("Presione ESC para salir."); 
	ENTER
	printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
	ENTER
	ENTER
	printf("Velocidad actual =  ");
	
	system("setterm -cursor off");
 	
	do{
	
			
			digitalWrite_D(sal[i], HIGH);		
			
			for(j = 0 ; j < retardo_3 ; j++) 
			{
				delay(1);
				printf("%d", rmap(retardo_3));
				refrescar();
				
				ch = getch();		
		
				retardo = retardo_3; 
				MODIFICAR_VELOCIDAD
				retardo_3 = retardo;
				
				if(ch == QUIT)
						break; 
			} 
			
			
			digitalWrite_D(sal[i], LOW);		
							
			if(i == tope)				
			{
					for(j = 0 ; j < 50 ; j++) 
				{
					delay(1);
					printf("%d", rmap(retardo_3));
					refrescar();
					
					ch = getch();		
			
					retardo = retardo_3; 
					MODIFICAR_VELOCIDAD
					retardo_3 = retardo;
					
					if(ch == QUIT)
							break; 
				} 
				digitalWrite_D(sal[i], HIGH);	
					
					for(j = 0 ; j < 50 ; j++) 
				{
					delay(1);
					printf("%d", rmap(retardo_3));
					refrescar();
					
					ch = getch();		
			
					retardo = retardo_3; 
					MODIFICAR_VELOCIDAD
					retardo_3 = retardo;
					
					if(ch == QUIT)
							break; 
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
			
			
	
 	
				
	}while( ch != QUIT); 
	
	system("setterm -cursor on");
	STOP_KEYBOARD
	APAGAR_LEDS		
}


void secuencia4 () 
{
  int sal[]={26, 21, 20, 16, 12, 25, 24, 23};	
  int i,j;		
  int ch;	
  int retardo;
  
   if( retardo_4 == -100)		
		est_vel(4);
	
	pioInit();					
		
	DECLARAR_SALIDAS
			
	i = 0;			
	
	INIT_KEYBOARD
	
	system("clear");   				
	printf("Secuencia \"El choque\".");
	ENTER
	printf("Presione ESC para salir.");
	ENTER 
	printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
	ENTER
	ENTER
	printf("Velocidad actual = ");
	system("setterm -cursor off");
	do{
					
			digitalWrite_D(sal[i], HIGH);		
			digitalWrite_D(sal[ VEC_SIZE-1-i ], HIGH);
			
			for(j=0 ; j < retardo_4 ; j++) 
			{
						delay(1);
						printf("%03d", rmap(retardo_4));
						refrescar();
						
						ch = getch();		
						
						retardo= retardo_4; 
						MODIFICAR_VELOCIDAD
						retardo_4 = retardo; 
						
						if (ch == QUIT)
							break; 			
			}
						
			digitalWrite_D(sal[i], LOW);
			digitalWrite_D(sal[ VEC_SIZE-1-i ], LOW);
		
			i++;
		
			if( i == 4 )		
				i = 5;
	
			if(i == VEC_SIZE)
				i = 1;
			
			
	
	}while( ch != QUIT); 
	
	system("setterm -cursor on");
	STOP_KEYBOARD
	APAGAR_LEDS

}




void control_remoto() 
{
	int op, ch, retardo;
	char ACK;
	char char_op;
	unsigned char velocidad = 0;
	
	system("clear");
	printf("Configuración del puerto \n \n ");
	system("setterm -cursor on");
	InitUart();
	
	do{
			system("clear");
			printf("Modo remoto.\n");
			printf("Seleccione una de las secuencias o presione ESC para salir.\n");
			printf("1  - Secuencia \"Auto Fantástico\".\n");
			printf("2  - Secuencia \"La Carrera\".\n");
			printf("3  - Secuencia \"La Apilada \".\n");
			printf("4  - Secuencia \"El Choque \".\n");
			printf("5  - Secuencia personalizada 1.\n");
			printf("6  - Secuencia personalizada 2.\n");
			printf("7  - Secuencia personalizada 3.\n");
			printf("8  - Secuencia personalizada 4.\n");
			printf("0 - Salir.\n\n");

			printf("Seleccione una opción: ");
			scanf("%d", &op);
			getchar();
			char_op = (char) (op + 48); 
			
			if( op > 0 && op < 9 )
			{
				
				write(puerto_serie, &char_op, 1);	
				
				ACK = 0;
				
				do{
					read(puerto_serie, &ACK, 1);
					printf("ACK %d \n", ACK);
					
				}while(ACK != 1);					
											
				switch(op)						
				{
					case 1: 
							if( retardo_1 == -100)		
								est_vel(1);
							ACK=0;
							do 
								{
									
									velocidad = (unsigned char) rmap(retardo_1);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							
							retardo=retardo_1;
							break;
					
					case 2: 
							if( retardo_2 == -100)		
								est_vel(2);
							
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_2);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							
							retardo=retardo_2;
							break;
							
					case 3: 
							if( retardo_3 == -100)		
								est_vel(3);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_3);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_3;
							break;
					
					case 4: 
							if( retardo_4 == -100)		
								est_vel(4);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_4);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_4;
							break;
							
					case 5: 
							if( retardo_5 == -100)		
								est_vel(5);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_5);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_5;
							break;
					
					case 6: 
							if( retardo_6 == -100)		
								est_vel(6);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_6);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_6;
							break;
							
					case 7: 
							if( retardo_7 == -100)		
								est_vel(7);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_7);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_7;
							break;
					
					case 8: 
							if( retardo_8 == -100)		
								est_vel(8);
							ACK=0;
							do 
								{
									velocidad = (unsigned char) rmap(retardo_8);
									write(puerto_serie, &velocidad, 1);
									read(puerto_serie, &ACK, 1);
									
							}while(ACK != 1);
							retardo=retardo_8;
							break;
				}
				

				INIT_KEYBOARD
				
				system("clear"); 
				
				switch(op)
					{
						case 1: printf("Secuencia \"Auto Fantástico\".");
								break;
						
						case 2: printf("Secuencia \"La Carrera\".");
								break;
								
						case 3: printf("Secuencia \"La Apilada\".");
								break;
					
						case 4: printf("Secuencia \"El Choque\".");
								break;
							
						case 5: printf("Secuencia personalizada 1.");
								break;
					
						case 6: printf("Secuencia personalizada 2.");
								break;
							
						case 7: printf("Secuencia personalizada 3.");
								break;
					
						case 8: printf("Secuencia personalizada 4.");
								break;
					}
					ENTER
									
					printf("Presione ESC para salir.");
					ENTER
					printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
					ENTER
					ENTER
					printf("Velocidad actual =  ");
					system("setterm -cursor off");
				
				do
				{
				  				
		
					printf("%03d", rmap(retardo)); 
					refrescar();
					
					ch = getch();		
															
					MODIFICAR_VELOCIDAD
					
					if(ch == KEY_UP || ch == KEY_DOWN){		
						velocidad =  rmap(retardo); 
						write(puerto_serie, &velocidad, 1);
					} 
				
				}while( ch != QUIT); 
				
				
				velocidad = 0;
				write(puerto_serie, &velocidad , 1);
				
				switch(op)						
				{
					case 1: retardo_1 = retardo;
							break;
					
					case 2: retardo_2 = retardo;
							break;
							
					case 3: retardo_3 = retardo;
							break;
				
					case 4: retardo_4 = retardo;
							break;
							
					case 5: retardo_5 = retardo;
							break;
					
					case 6: retardo_6 = retardo;
							break;
							
					case 7: retardo_7 = retardo;
							break;
					
					case 8: retardo_8 = retardo;
							break;
				}
				system("setterm -cursor on");
				STOP_KEYBOARD
		}
		else if(op != 0)
		{
			printf("\nOpción no valida, intente nuevamente.");
			getchar();	
		}
  		 
   }while(op != 0);
   
}




int tab_dat(int estados, char sec[], int secuencia) 
{
	
	char aux = 0b10000000;
	int ch;
	int i, j;
	int retardo=1;  
	
	
	  system("clear");   				
		switch(secuencia)
		{
			case 2: printf("Secuencia \"La carrera\""); ENTER
					break;
					
			case 5: printf("Secuencia personalizada 1"); ENTER
					break;
					
			case 6: printf("Secuencia personalizada 2"); ENTER 
					break;				
					
		}		
		
		
		printf("Presione ESC para salir."); 
		ENTER
		printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
		ENTER
		ENTER
		system("setterm -cursor off");
		printf("Velocidad actual =    ");
		
	do {
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
					switch(secuencia)		
					{
						case 2: printf("%03d", rmap(retardo_2));
								break;
							
						case 5: printf("%03d", rmap(retardo_5));
								break;
							
						case 6: printf("%03d", rmap(retardo_6));
								break;				
					}
				
					refrescar();
					ch = getch();		
				
					if(ch == QUIT)
							return 1;
				
					switch(secuencia)		
					{
						case 2: retardo = retardo_2;
										break;
							
						case 5: retardo = retardo_5;
										break;
							
						case 6: retardo = retardo_6;
										break;				
					}
									
					MODIFICAR_VELOCIDAD
						
				
					switch(secuencia)		
					{
						case 2: retardo_2 = retardo;
										break;
							
						case 5: retardo_5 = retardo;
										break;
							
						case 6: retardo_6 = retardo;
										break;				
							
					
					}
				delay(1);	
				}
				
			}
	}while(ch != QUIT);
			
			system("setterm -cursor on");
			return 0;		
}


void map(int sec, int val) 
{
	int retardo;

	if(val > 206 ) 
		retardo =  256-val; 
	else if (val <= 206) 
		retardo= ((206-val)*10) + CAM_PASO; 
		
		switch(sec) {
			
		case 1: retardo_1 = retardo; break; 
		
		case 2: retardo_2 = retardo; break;
		
		case 3: retardo_3 = retardo; break;
		
		case 4: retardo_4 = retardo; break;
		
		case 5: retardo_5 = retardo; break;
		
		case 6: retardo_6 = retardo; break;
		
		case 7: retardo_7 = retardo; break; 
		
		case 8: retardo_8 = retardo; break; 
	
			}
	
}

int	rmap(int retardo)
{
	if (retardo < 50 )
		return (256 - retardo);
	
	else if (retardo >= 50) 
		return (206 - ((retardo - CAM_PASO) / 10 ));
	
}



void refrescar(void) 
{
			int i; 
			char ch=8;
			for(i=0; i < 3; i++) 
				printf("%c",ch); 
			
}


void secuencia5() 
{

   
   unsigned char secuencia[256] = {0};
   int i;
   
   if( retardo_5 == -100)
		est_vel(5);
	
	pioInit();			
		
  DECLARAR_SALIDAS

  for(i=0; i < 256 ; i++)
    secuencia[i] = i; 
	
	i = 0;			
	
	INIT_KEYBOARD
	
  tab_dat ( 256, secuencia, 5) ; 

  STOP_KEYBOARD
  APAGAR_LEDS
}

void secuencia7 () 
{
  
  int i,j;		
  int ch;	
  int retardo;
  
   if( retardo_7 == -100)		
		est_vel(7);
	
	pioInit();					
		
    DECLARAR_SALIDAS
				
	i = 3;			
	
	INIT_KEYBOARD
	
	system("clear");   				
	printf("Secuencia Personalizada 3.");
	ENTER
	printf("Presione ESC para salir.");
	ENTER 
	printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
	ENTER
	ENTER
	printf("Velocidad actual = ");
	
	system("setterm -cursor off");
	
	do{
	 
      
      digitalWrite_D( sal[i], !digitalRead_D(sal[i]) );
      digitalWrite_D( sal[VEC_SIZE -1 -i], !digitalRead_D( sal[VEC_SIZE -1 -i]) );
      i--; 
      for(j=0 ; j < retardo_7 ; j++)
        {
            delay(1);
						printf("%03d", rmap(retardo_7));
						refrescar();
						
						ch = getch();		
						
						retardo= retardo_7; 
						MODIFICAR_VELOCIDAD
						retardo_7 = retardo; 
						
						if (ch == QUIT)
							break; 			
        }
			
	  if(i == -1) 
      i = 3; 

	}while( ch != QUIT); 
	
	system("setterm -cursor on");
	STOP_KEYBOARD
	
	APAGAR_LEDS
  
}

void secuencia6 (void)
{
	
	char secuencia[] = {0b11000000, 0b00000011, 0b00110000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000 ,0b00100000, 0b01000000, 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b11111111, 0};
   int i;
   
   if( retardo_6 == -100)		
		est_vel(6);
	
	pioInit();					
		
	for( i = 0 ; i < VEC_SIZE ; i++	)
		pinMode_D( sal[i], OUTPUT);
				
	i = 0;			
	
	INIT_KEYBOARD
	
  tab_dat ( (int) strlen(secuencia), secuencia, 6) ; 

  STOP_KEYBOARD

  APAGAR_LEDS		

}

void secuencia8 () 
{
  
  int i,j;		
  int ch;	
  int retardo;
  int apagar = 1;
  
   if( retardo_8 == -100)		
		est_vel(8);
	
	pioInit();					
		
  DECLARAR_SALIDAS
				
	i = 0;			
	
	INIT_KEYBOARD
	
	system("clear");   				
	printf("Secuencia Personalizada 4.");
	ENTER
	printf("Presione ESC para salir.");
	ENTER 
	printf("Flecha UP para aumentar la velocidad - Flecha DOWN para disminuir la velocidad.");
	ENTER
	ENTER
	printf("Velocidad actual = ");
	
	system("setterm -cursor off");
	
	do{
	 
      
      digitalWrite_D( sal[i], HIGH );
      			
      for(j=0 ; j < retardo_8 ; j++)
        {
            delay(1);
						printf("%03d", rmap(retardo_8));
						refrescar();
						
						ch = getch();		
						
						retardo= retardo_8; 
						MODIFICAR_VELOCIDAD
						retardo_8 = retardo; 
						
						if (ch == QUIT)
							break; 			
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
					
					for( j = 0 ; j < VEC_SIZE ; j++	)
						digitalWrite_D(sal[j], 0);		
						
					delay(30);	
			}
			
			apagar = !apagar;
			i = 0;
		}	 	
    
    else
       i += 2;
     
       

	}while( ch != QUIT); 
	
	system("setterm -cursor on");
	STOP_KEYBOARD
	APAGAR_LEDS 
  
}




