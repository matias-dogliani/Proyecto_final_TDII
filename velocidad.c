#include "TP_FINAL.h"
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


