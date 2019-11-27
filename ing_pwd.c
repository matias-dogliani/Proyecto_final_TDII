#include "TP_FINAL.h"

int intentos=0;

int ing_pwd(void) 
{
	while(intentos<3)
	{
		if(valid_pwd())
			intentos++;
		else
		{
			system("clear");
			printf("Bienvenido al sistema.");
			getchar();
			//break;
			return 1;
		}
	}
		
	return 0;
	
}



int valid_pwd(void){
	
	char ch_in[LONG_PWD]= {0} ;
	char ch_as=CHAR_ECHO;
	char ch_cmp[]= "doris";
	int i=0; 	
	
	printf("Ingrese contraseña: \n"); 
	keyboard_start();
	
	do{
		if (read(0,&ch_in[i],1) > 0){
			if(ch_in[i] == OUT_CHAR) 
				break;				
			write(1,&ch_as,1);
			i++;
			}
		
	}while ( i<LONG_PWD );

	keyboard_stop();
		
	for(i=0; i<strlen(ch_cmp) ; i++)		
		if(ch_cmp[i] != ch_in[i]){
			printf("\nContraseña incorrecta. ");
			if(intentos<2)
				printf("Por favor, intente nuevamente (%d intentos restantes).", 2-intentos);
			else
				printf("Se han terminado los intentos.\n");
			getchar();
			system("clear");	
			return 1;
			}		
	

	return 0;		

	}
