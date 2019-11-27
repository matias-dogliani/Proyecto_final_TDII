#include "TP_FINAL.h"

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






