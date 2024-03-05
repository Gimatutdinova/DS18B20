#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NO_ID 0xCC
#define T_CONVERT 0x44
#define READ_DATA 0xBE

#define PORT_TEMP PORTC
#define DDR_TEMP DDRC
#define PIN_TEMP PINC
#define BIT_TEMP 1

int get_temp(void);
char DS18B20_init(void);
void DS18B20_send(uint8_t data);
int DS18B20_read(void);

#endif /* DS18B20_H_ */