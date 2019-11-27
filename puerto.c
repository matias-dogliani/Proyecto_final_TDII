
#include "TP_FINAL.h"

int InitUart(void){ 
 
                   
  char puerto[12] = "/dev/ttyS0" ; 
  
  int bits_datos; 
  char paridad; 
  int bits_parada; 
  int speed; 
  struct termios opciones;
    
  
  printf("Ingrese el número del puerto [/dev/ttySX] : " );
  scanf("%c", &puerto[9]);
  printf("\n");
  getchar();

   
  
 
  printf("Ingrese los bits de datos ( 5 < N < 8) " );
  scanf("%d", &bits_datos);
  printf("\n");
  getchar();
  
  if(bits_datos < 5 || bits_datos >8)
  {
    printf("Bits de datos inválidos \n");
    exit(1);
   }
 
  printf("Ingrese tipo de paridad (E: Even - N: No parity - O: Odd)  :   " );
  scanf("%c", &paridad);
  printf("\n");
   getchar();
  
  if( (toupper(paridad) != 'N') && (toupper(paridad) != 'E') &&
      (toupper(paridad) != 'O') ) {
    printf( "Error de paridad. Debe ser N, E, O\n" );
    exit( 1 );
  }

  
  printf("Ingrese cantidad de bits de parada (1 - 2)  :   " );
  scanf("%d", &bits_parada);
  printf("\n");
   getchar();
   if( (bits_parada< 1) || (bits_parada > 2) ) {
    printf( "Error. Bits de stop debe ser 1 ó 2\n" );
    exit( 1 );
  }

  puerto_serie = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
  if (puerto_serie == -1) {
    printf("Error al abrir de puerto \n");
    exit( 1 );
  }


  printf("Ingrese velociadd de transmisión (Baudios)  :   " );
  scanf("%d", &speed);
   getchar();
  printf("\n");
  
   tcgetattr( puerto_serie, &opciones );

    /*   CONFIGURACIÓN DEL PUERTO     */

  fcntl(puerto_serie, F_SETFL, FNDELAY); 
  cfsetispeed( &opciones, velocidad( speed) );

  opciones.c_cflag |= (CLOCAL | CREAD);

  
   switch( bits_datos) {
    case 5: bits_datos = CS5; break;
    case 6: bits_datos = CS6; break;
    case 7: bits_datos = CS7; break;
    case 8: bits_datos = CS8; break;
  }
  
  opciones.c_cflag &= ~CSIZE; 
  opciones.c_cflag |= bits_datos; 


  if( bits_parada == 1 )
    opciones.c_cflag &= ~CSTOPB;
  else
    opciones.c_cflag |= CSTOPB;

 
  if( toupper(paridad) == 'N' )
    opciones.c_cflag &= ~PARENB;

  if( toupper(paridad) == 'E' ) {
    opciones.c_cflag |= PARENB;
    opciones.c_cflag &= ~PARODD;
  }

  if( toupper(paridad) == 'O' ) {
    opciones.c_cflag |= PARENB;
    opciones.c_cflag |= PARODD;
  }

 
  opciones.c_lflag &= ~(ECHO | ICANON | ISIG);
  opciones.c_oflag &= ~OPOST;
  opciones.c_cc[VTIME] = 0;
  opciones.c_cc[VMIN] = 1;

 
  tcsetattr( puerto_serie, TCSANOW, &opciones );


  
}



int velocidad( int speed ) { 
  switch( speed ) {
    case 50: return( B50 );
    case 75: return( B75 );
    case 110: return( B110 );
    case 134: return( B134 );
    case 150: return( B150 );
    case 200: return( B200 );
    case 300: return( B300 );
    case 600:return( B600 );
    case 1200: return( B1200 );
    case 1800: return( B1800 );
    case 2400: return( B2400 );
    case 4800: return( B4800 );
    case 9600: return( B9600 );
    case 19200: return( B19200 );
    case 38400: return( B38400 );
    case 57600: return( B57600 );
    case 115200: return( B115200 );
    default: printf ( "Error velocidad no permitida\n" ); 
             exit(1);
             break;
  }
}
