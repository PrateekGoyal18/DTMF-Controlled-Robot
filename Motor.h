#include<avr/io.h>

void forward();
void reverse();
void stop();
void diff_right();
void axial_right();
void diff_left();
void axial_left();

void forward()
{
  PORTB = 0b00001010;
}

void reverse()
{
  PORTB = 0b00000101; 
}

void stop()
{
  PORTB = 0b00000000;
}

void diff_right()
{
  PORTB = 0b00000010;
}

void axial_right()
{
  PORTB = 0b00000110;
}

void diff_left()
{
  PORTB = 0b00000001;
}

void axial_left()
{
  PORTB = 0b00001001;
}
