#define M1_PORT PORTA
#define M1_PIN PINA
#define M1_DDR DDRA
#define M1_EN 4
#define M1_A 5
#define M1_B 3
#define M1 OCR1A
#define M1_PWM_DDR DDRD 
#define M1_PWM 4 //OCR1A - PD5

#define M2_PORT PORTA
#define M2_PIN PINA
#define M2_DDR DDRA
#define M2_EN 2
#define M2_A 7
#define M2_B 6
#define M2 OCR1B
#define M2_PWM_DDR DDRD
#define M2_PWM 5 //OCR1B - PD4


void motor_init();

char m1_overload();

void m1_start();

void m1_stop();

void m1_set(char power);

char m2_overload();

void m2_start();

void m2_stop();

void m2_set(char power);
