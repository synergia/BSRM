#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../lib/usart/usart.h"
#include "motor.h"

#define MY_ID 1


USART32(uart);



void pwm_init(){
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

void wait(){
	while (uart.empty());
}

int size(unsigned char primitive){
	switch (primitive){
		case 4: return 2;
	}
}

int main()
{
	
	unsigned char adress;
	unsigned char primitive;
	unsigned char trash;
	
	pwm_init();
	motor_init();
	sei();


	//m2_start();
	//m1_start();

	
	
	uart << "**** BSRM01 v.0.00001 ready. ****\r\n";
	
	 while(1){
				
		//wait();
		//uart >> adress;	
		//adress-=48;	
							
		//if (adress == MY_ID){
			
			wait();
			uart >> primitive;	
	
			switch (primitive){
				case 'S':
					m1_stop();
					m2_stop();
					uart << "BSRM01: M1, M2 STOP!";
				case 'E': 
				
					unsigned char eng;
					unsigned char power;
											
					wait();		
					uart >> eng;
					wait();
					uart >> power;
						
					if (eng == 0){
						uart <<"E0:" << (int)power <<"%";
						m1_set(power);
						m1_start();			
					}
					else if (eng == 1){
						uart <<"E1:" << (int)power <<"%";
						m2_set(power);
						m2_start();
					}
					break;
				
			}
													
		}
		// else {
		// 			uart << "Are you talking to me, dude?\r\n";
		// 			wait();
		// 			uart >> primitive;
		// 			for(int i = 0; i < size(primitive); i++){
		// 				wait();
		// 				uart >> trash;
		// 			}
		// 		}	
	//}
}