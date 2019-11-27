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


