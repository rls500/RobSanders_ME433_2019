#ifndef Expandedr
#define Expander

#include <xc.h>
#include <sys/attribs.h>
#include "I2C.h"

#define SLAVE_ADDR 0b0100111
#define GPIO 0x09
#define OLAT 0x0A
#define IODIR 0x00
#define IOCON 0x05


void initExpander();
void setExpander(char pins, char level);
unsigned char getExpander();

#endif