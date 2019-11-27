#include "TP_FINAL.h"

void keyboard_start(void) 
{
	tcgetattr(0,&initial_settings_keyboard);
	new_settings_keyboard = initial_settings_keyboard;
	new_settings_keyboard.c_lflag &= ~ICANON;  
	new_settings_keyboard.c_lflag &= ~ECHO;
	new_settings_keyboard.c_lflag &= ~ISIG;   
	new_settings_keyboard.c_cc[VMIN] = 0; 
	new_settings_keyboard.c_cc[VTIME] = 0; 
	tcsetattr(0, TCSANOW, &new_settings_keyboard);
}

void keyboard_stop(void) 
{
	tcsetattr(0, TCSANOW, &initial_settings_keyboard); 
}
