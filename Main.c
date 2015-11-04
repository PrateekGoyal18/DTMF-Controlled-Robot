// Project name : DTMF controlled robot for Atmega16 with LCD interfacing

#include<motor.h>
#include<util/delay.h>
#include<LCD_mega128.h>

void main()
{
  // LCD initialization
  lcd_init();
  lcd_cmd(0x01);

  // DTMF intialization
  DDRD = 0b000000000;
  PORTD = 0xff;

  // MOTORS initialization
  DDRB = 0xFF;

  while(1)
  {
    if((PINA&15)==2)     // if Key 2 of cell phone pressed
        forward();
        lcd_string("Moving Straight");
        while(1)
        {
            lcd_cmd(0x18);
            _delay_ms(1000);
        }

	if((PINA&15)==4)     // if Key 4 of cell phone pressed
        axial_left();
        lcd_string("Turning Left");
        while(1)
        {
            lcd_cmd(0x18);
            _delay_ms(1000);
        }

	if((PINA&15)==6)     // if Key 6 of cell phone pressed
        axial_right();
        lcd_string("Turning Right");
        while(1)
        {
            lcd_cmd(0x18);
            _delay_ms(1000);
        }

    if((PINA&15)==8)     // if Key 8 of cell phone pressed
        reverse();
        lcd_string("Reversing");
        while(1)
        {
            lcd_cmd(0x18);
            _delay_ms(1000);
        }

    if((PINA&15)==5)     // if Key 5 of cell phone pressed
        stop();
        lcd_string("Stopped");
        while(1)
        {
            lcd_cmd(0x18);
            _delay_ms(1000);
        }
  }
}
