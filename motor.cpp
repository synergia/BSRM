#include <avr/io.h> 
#include <util/delay.h>
#include "motor.h"

volatile char m1_power = 0;
volatile char m1_state = 0;

volatile char m2_power = 0;
volatile char m2_state = 0;

void motor_init(){
	M1_DDR |= (1 << M1_A) | (1 << M1_B);
	M2_DDR |= (1 << M2_A) | (1 << M2_B);
	M1_PORT |= (1 << M1_EN);
    M2_PORT |= (1 << M2_EN);
	M1_PWM_DDR |= (1 << M1_PWM);
    M2_PWM_DDR |= (1 << M2_PWM);
	M1 = 0;
	M2 = 0;
	m1_state = 0;
	m2_state = 0;
}

char m1_overload(){
	if (bit_is_set(M1_PIN, M1_EN)) return 0;
	else return 1;
}

void m1_start()
{
	if (m1_power < 0){
		M1_PORT |= (1 << M1_A);
		M1_PORT &= ~(1 << M1_B);
		unsigned char tmp = -m1_power*255/100;
		M1 = tmp;
	}
	else{
		M1_PORT &= ~(1 << M1_A);
		M1_PORT |= (1 << M1_B);
		unsigned char tmp = m1_power*255/100;
		M1 = tmp;
	}
	m1_state = 1;
}

void m1_stop(){
	M1_PORT |= (1 << M1_A);
	M1_PORT |= (1 << M1_B);
	m1_state = 0;
	//_delay_ms(100);
}

void m1_set(char power){
	int tmp = power * m1_power;
	if (power < -100) power = -100;
	if (power > 100) power = 100;
	if (tmp <= 0)
	{
		m1_power = power;
		if (m1_state == 1){
			m1_stop();
			_delay_ms(20);
			m1_start();
		}
	}
	else{
		m1_power = power;
		if (m1_state == 1) m1_start();
	}
}

char m2_overload(){
	if (bit_is_set(M2_PIN, M2_EN)) return 0;
	else return 1;
}

void m2_start()
{
	if (m2_power < 0){
		M2_PORT |= (1 << M2_A);
		M2_PORT &= ~(1 << M2_B);
		unsigned char tmp = -m2_power*255/100;
		M2 = tmp;
	}
	else{
		M2_PORT &= ~(1 << M2_A);
		M2_PORT |= (1 << M2_B);
		unsigned char tmp = m2_power*255/100;
		M2 = tmp;
	}
	m2_state = 1;
}

void m2_stop(){
	M2_PORT |= (1 << M2_A);
	M2_PORT |= (1 << M2_B);
	m2_state = 0;
	//_delay_ms(20);
}

void m2_set(char power){
	int tmp = power * m2_power;
	if (power < -100) power = -100;
	if (power > 100) power = 100;
	if (tmp <= 0)
	{
		m2_power = power;
		if (m2_state == 1){
			m2_stop();
			_delay_ms(20);
			m2_start();
		}
	}
	else{
		m2_power = power;
		if (m2_state == 1) m2_start();
	}
}