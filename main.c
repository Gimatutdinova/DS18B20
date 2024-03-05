#include "main.h"

int time = 1;
int stop = 0;

ISR(TIMER1_OVF_vect) { time = 1; }
ISR(INT1_vect) { stop = 1; }

int main(void) {
  port_init();
  int temp = 0;
  int sign = 0;
  while (1) {
    if (PIN_BUTTON_IND == (0b0 | (1 << STOP_BUTTON))) {
      while (1) {
        if (stop) {
          stop_ind();
          break;
        }
        if (time) {
          TCCR1B = 0b00000000;
          temp = get_temp();
          if (temp < 0) {
            sign = 1;
            temp *= -1;
          }
          temp = temp * 10 >> 4;
          time = 0;
          TCCR1B = 0b00000011;
        }

        light_led(temp / 10);

        int integer = temp / 10;
        if ((integer / 10) != 0) {
          if (sign) display_temp(10, ONE_NUM);
          display_temp(integer / 10, TWO_NUM);
          integer = integer % 10;
        } else if (sign)
          display_temp(10, TWO_NUM);
        display_temp(integer, THREE_NUM);
        if (sign)
          display_temp((temp % 10) + 1, FOUR_NUM);
        else
          display_temp((temp % 10), FOUR_NUM);
      }
    }
  }
}

void port_init(void) {
  DDR_IND = 0xFF;
  PORT_IND = 0x00;

  DDR_LED = 0xFF;
  PORT_LED = 0x00;

  DDR_BUTTON_IND = 0b0 | (1 << ONE_NUM) | (1 << TWO_NUM) | (1 << THREE_NUM) |
                   (1 << FOUR_NUM);
  PORT_BUTTON_IND = 0b0 | (1 << START_BUTTON) | (1 << STOP_BUTTON);

  TIMSK |= (1 << 2);
  TCNT1 = 60000;
  GICR = 0b11000000;
  MCUCR = 0b00000010;

  sei();
}

void light_led(int temp) {
  if (temp == STANDART_TEMP)
    PORT_LED = GREEN;
  else if (temp > STANDART_TEMP)
    PORT_LED = RED;
  else
    PORT_LED = BLUE;
}

void display_temp(int temp, int bit) {
  PORT_BUTTON_IND = 0b0 | (1 << START_BUTTON) | (1 << STOP_BUTTON) | (1 << bit);
  switch (temp) {
    case 0:
      PORT_IND = ZERO;
      break;
    case 1:
      PORT_IND = ONE;
      break;
    case 2:
      PORT_IND = TWO;
      break;
    case 3:
      PORT_IND = THREE;
      break;
    case 4:
      PORT_IND = FOUR;
      break;
    case 5:
      PORT_IND = FIVE;
      break;
    case 6:
      PORT_IND = SIX;
      break;
    case 7:
      PORT_IND = SEVEN;
      break;
    case 8:
      PORT_IND = EIGHT;
      break;
    case 9:
      PORT_IND = NINE;
      break;
    default:
      PORT_IND = MINUS;
      break;
  }
  if (bit == THREE_NUM) PORT_IND |= POINT;
  _delay_ms(5);
  PORT_IND = 0;
}

void stop_ind(void) {
  PORT_BUTTON_IND = 0b0 | (1 << START_BUTTON) | (1 << STOP_BUTTON);
  PORT_IND = 0;
  PORT_LED = 0;
  _delay_ms(80);
  PORT_LED = RED;
  _delay_ms(80);
  PORT_LED = 0;
  _delay_ms(80);
  PORT_LED = RED;
  _delay_ms(80);
  PORT_LED = 0;
  _delay_ms(80);
  PORT_LED = RED;
  _delay_ms(80);
  PORT_LED = 0;
  stop = 0;
}