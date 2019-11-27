#include <sys/mman.h>
#include <fcntl.h>


#define GPIO_BASE  0x3F200000	
#define BLOCK_SIZE (4*1024)   
#define GPFSEL 	 (volatile unsigned int *) (gpio)			
#define	GPSET	 (volatile unsigned int *) (gpio + 7)   
#define GPCLR	 (volatile unsigned int *) (gpio + 10)
#define	GPLEV	 (volatile unsigned int *) (gpio + 13)
#define	INPUT 0
#define OUTPUT 1
#define ALT0 4
#define HIGH 1
#define LOW 0



volatile unsigned int *gpio; 




void pioInit(){
	int fd;
	void *reg_map; 
	fd = open("/dev/gpiomem", O_RDWR|O_SYNC); 
	reg_map = mmap(
	NULL,   			
	BLOCK_SIZE,
	PROT_READ|PROT_WRITE,
	MAP_SHARED,		
	fd,
	GPIO_BASE); 

	gpio = (volatile unsigned *)reg_map;  
	close(fd);
}


void pinMode_D(int num_pin, int modo)
{
	
	int num_reg,offset;
	
	num_reg= num_pin/10;
	offset= (num_pin % 10 ) * 3; 	
	
	*(GPFSEL + num_reg) &= ~((0b111 & ~modo) << offset);		
	*(GPFSEL + num_reg) |= ((0b111 & modo) << offset);		

}

void digitalWrite_D(int num_pin, int value )
{
	
	int num_reg,offset;	
	num_reg= num_pin/32;
	offset= num_pin % 32; 	

	if(value)
		*(GPSET + num_reg) = 1 << offset;
	else 
		*(GPCLR + num_reg) = 1 << offset;			

}

int digitalRead_D(int num_pin) {
	
int num_reg,offset;	
	num_reg= num_pin/32;
	offset= num_pin % 32;  

	if( *(GPLEV+num_reg) & (0b1 << offset))
		return 1;

	else 
		return 0; 
	

}








