

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


#define QUIT 27
#define LONG_PWD 100
#define OUT_CHAR 10
#define CHAR_ECHO 42 
#define VEL_LENGHT 22

  
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




static struct termios initial_settings, new_settings; //para el puerto 
static struct termios initial_settings_keyboard, new_settings_keyboard;  //para el teclado 
int puerto_serie; 









