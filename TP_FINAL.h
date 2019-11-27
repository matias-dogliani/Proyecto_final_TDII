

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 	
#include <sys/ioctl.h> 	
#include <termios.h> 	
#include <ctype.h> 
#include "GPIO_D.h"
#include <ncurses.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>


#define QUIT 27
#define LONG_PWD 100
#define OUT_CHAR 10
#define CHAR_ECHO 42 
#define VEL_LENGHT 22
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

  
int valid_pwd(void);
int ing_pwd(void); 
int menu (void); 
void secuencia1 (void);
void secuencia2 (void);
void secuencia3 (void);
void secuencia4 (void);
void secuencia5 (void);
void secuencia6 (void);
void secuencia7 (void);
void secuencia8 (void);
void leer_ADC(); 
void control_remoto(void); 
int tab_dat(int estados, char sec[], int); 
void keyboard_stop(void);
void keyboard_start(void); 
int InitUart(void); 
int velocidad( int speed ); 
void map(int sec, int val);
int rmap(int retardo);
void refrescar(void);
void est_vel(int sec);



static struct termios initial_settings, new_settings; //para el puerto 
static struct termios initial_settings_keyboard, new_settings_keyboard;  //para el teclado 
int puerto_serie; 
int sal[]={26, 21, 20, 16, 12, 25, 24, 23};	
int retardo_1 = -100; 		
int retardo_2 = -100;
int retardo_3 = -100;
int retardo_4 = -100;
int retardo_5 = -100;
int retardo_6 = -100;
int retardo_7 = -100;
int retardo_8 = -100;








