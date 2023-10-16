#include <avr/io.h>
#include <avr/interrupt.h>

//void Timer0_init();
void Timer3_init();
//void init_interrupt_timer0_nor();
//void init_interrupt_timer0_ctc();
void init_interrupt_timer3_ctc();
void led_init();
void led_put(uint8_t led);

uint8_t current_led_state=0x00;
unsigned int counter=0;



int main(void)
{
	led_init();
	Timer3_init();
	/* Replace with your application code */
	while (1)
	{
	}
}

//1 ms
/*ISR(TIMER0_COMP_vect){
	
	counter+=1;
	if(counter==1000){
		counter=0;
		current_led_state=current_led_state^0x0F;
		//Toggle LED
		led_put(current_led_state);
	}
}*/


/*void Timer0_init()
{
	const uint8_t mode_nor=(0<<WGM30)|(0<<WGM31);
	const uint8_t mode_pwm=(0<<WGM30)|(1<<WGM01);
	const uint8_t mode_ctc=(1<<WGM00)|(0<<WGM01);
	const uint8_t mode_fpwm=(1<<WGM00)|(1<<WGM01);
	
	const uint8_t pres_0=(0<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_1=(0<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_8=(0<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_32=(0<<CS02)|(1<<CS01)|(1<<CS00);
	const uint8_t pres_64=(1<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_128=(1<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_256=(1<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_1024=(1<<CS02)|(1<<CS01)|(1<<CS00);
	//set mode for timer 0
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_64|mode_ctc;
	
	OCR0=124;
	
	// set interrupt
	init_interrupt_timer0_ctc();
	
}*/
void init_interrupt_timer3_ctc()
{
	ETIMSK|=1<<TOIE3;
	sei();
}
ISR(TIMER3_OVF_vect)
{
			counter+=1;
			if(counter==1000){
				counter=0;
				current_led_state=current_led_state^0x0F;
				//Toggle LED
				led_put(current_led_state);}
}
void Timer3_init()
{
	const uint8_t mode_B_nor=(0<<WGM33)|(0<<WGM32);
	const uint8_t mode_A_nor=(0<<WGM31)|(0<<WGM30);

	const uint8_t mode_B_ctc=(0<<WGM33)|(1<<WGM32);
	const uint8_t mode_A_ctc=(0<<WGM31)|(0<<WGM30);
	
	// mode for OCRnA
	
	const uint8_t pres_0=(0<<CS32)|(0<<CS31)|(0<<CS30);
	const uint8_t pres_1=(0<<CS32)|(0<<CS31)|(1<<CS30);
	const uint8_t pres_8=(0<<CS32)|(1<<CS31)|(0<<CS30);
	const uint8_t pres_64=(0<<CS32)|(1<<CS31)|(1<<CS30);
	const uint8_t pres_256=(1<<CS32)|(0<<CS31)|(0<<CS30);
	const uint8_t pres_1024=(1<<CS32)|(0<<CS31)|(1<<CS30);
	const uint8_t pres_clkfall=(1<<CS32)|(1<<CS31)|(0<<CS30);
	const uint8_t pres_clkrise=(1<<CS32)|(1<<CS31)|(1<<CS30);
	//set mode for timer 3
	const uint8_t des_nor_nonpwm= (0<<COM3A0)|(0<<COM3B0)|(0<<COM3C0)|(0<<COM3A1)|(0<<COM3B1)|(0<<COM3C1);
	const uint8_t des_toggle_nonpwm= (0<<COM3A0)|(0<<COM3B0)|(0<<COM3C0)|(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1);
	const uint8_t des_clear_nonpwm= (1<<COM3A0)|(1<<COM3B0)|(1<<COM3C0)|(0<<COM3A1)|(0<<COM3B1)|(0<<COM3C1);
	const uint8_t des_set_nonpwm= (1<<COM3A0)|(1<<COM3B0)|(1<<COM3C0)|(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1);
	
    TCCR3A=des_nor_nonpwm|mode_A_nor;
	TCCR3B=(0<<ICNC3)|(0<<ICES3)|mode_B_nor|pres_1;
	TCCR3C=0x00;
	init_interrupt_timer3_ctc();
}

/*void init_interrupt_timer0_ctc(){
	TIMSK=0x02;
	sei();
}*/

void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led)
{
	PORTB=led << 4;
	PORTD=led;
}
