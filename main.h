#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <asf.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "DS18B20.h"

enum Numbers {
  ZERO = 0b11111100,
  ONE = 0b01100000,
  TWO = 0b11011010,
  THREE = 0b11110010,
  FOUR = 0b01100110,
  FIVE = 0b10110110,
  SIX = 0b10111110,
  SEVEN = 0b11100000,
  EIGHT = 0b11111110,
  NINE = 0b11110110,
  POINT = 0b00000001,
  MINUS = 0b00000010,
};

enum Colors {
  RED = 0b00000100,
  GREEN = 0b00001000,
  BLUE = 0b00010000,
};

#define PORT_BUTTON_IND PORTD
#define PORT_LED PORTC
#define PORT_IND PORTB

#define DDR_BUTTON_IND DDRD
#define DDR_LED DDRC
#define DDR_IND DDRB

#define PIN_BUTTON_IND PIND
#define PIN_LED PINC
#define PIN_IND PINB

#define STANDART_TEMP 23

#define START_BUTTON 2
#define STOP_BUTTON 3

#define ONE_NUM 4
#define TWO_NUM 5
#define THREE_NUM 6
#define FOUR_NUM 7

void port_init(void);
void light_led(int temp);
void display_temp(int temp, int bit);
void stop_ind(void);

#endif /* MAIN_H_ */