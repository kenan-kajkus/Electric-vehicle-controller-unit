/*
 * timer.c
 *
 * Created: 16.07.2020 11:54:14
 *  Author: Kenan Kajkus
 */ 
 #include <avr/interrupt.h>
 #include <util/atomic.h>

 volatile unsigned long timer1_millis;

 void startTimer()
 {
	cli(); // stop interrupts
	TCCR0A = 0; // set entire TCCR0A register to 0
	TCCR0B = 0; // same for TCCR0B
	TCNT0  = 0; // initialize counter value to 0
	// set compare match register for 1000 Hz increments
	OCR0A = 249; // = 16000000 / (64 * 1000) - 1 (must be <256)
	// turn on CTC mode
	TCCR0B |= (1 << WGM01);
	// Set CS02, CS01 and CS00 bits for 64 prescaler
	TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
	// enable timer compare interrupt
	TIMSK0 |= (1 << OCIE0A);
	sei(); // allow interrupts
 }

  unsigned long millis ()
  {
	  unsigned long millis_return;

	  // Ensure this cannot be disrupted
	  ATOMIC_BLOCK(ATOMIC_FORCEON) {
		  millis_return = timer1_millis;
	  }
	  
	  return millis_return;
  }

  void wait(unsigned long waitMills)
  {
	  unsigned long start = millis();
	  while ( start+waitMills > millis())
	  {
	  }
  }

  ISR (TIMER0_COMPA_vect)
  {
	  timer1_millis++;
  }