#include "DS18B20.h"

int get_temp(void) {
  int temp = 0;
  int l_byte, h_byte;
  if (DS18B20_init() == 1) {
    DS18B20_send(NO_ID);
    DS18B20_send(T_CONVERT);
    _delay_ms(750);
    DS18B20_init();
    DS18B20_send(NO_ID);
    DS18B20_send(READ_DATA);
    l_byte = DS18B20_read();
    h_byte = DS18B20_read();
    temp = (((h_byte << 8) | l_byte));
  }
  return temp;
}

char DS18B20_init(void) {
  char device = 0;
  DDR_TEMP |= (1 << BIT_TEMP);
  _delay_us(485);
  DDR_TEMP &= ~(1 << BIT_TEMP);
  _delay_us(65);
  if ((PIN_TEMP & (1 << BIT_TEMP)) == 0) device = 1;
  _delay_us(420);
  return device;
}

void DS18B20_send(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    DDR_TEMP |= (1 << BIT_TEMP);
    _delay_us(2);
    if ((data & (1 << i)) == 1 << i) DDR_TEMP &= ~(1 << BIT_TEMP);
    _delay_us(65);
    DDR_TEMP &= ~(1 << BIT_TEMP);
    _delay_us(2);
  }
}

int DS18B20_read(void) {
  int byte = 0;
  for (uint8_t i = 0; i < 8; i++) {
    DDR_TEMP |= (1 << BIT_TEMP);
    _delay_us(2);
    DDR_TEMP &= ~(1 << BIT_TEMP);
    _delay_us(13);
    byte |= ((PIN_TEMP & (1 << BIT_TEMP)) >> BIT_TEMP) << i;
    _delay_us(45);
  }
  return byte;
}