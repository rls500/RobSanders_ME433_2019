#ifndef __IMU_h_
#define __IMU_h_

#define IMU_ADDR 0b1101011
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define CTRL3_C 0x12
#define WHOAMI 0x0F
#define OUT_TEMP_L 0x20
#define OUTX_L_XL 0x28
#define OUTX_L_G 0x22

void IMU_init();
unsigned char IMU_read(char reg);
void I2C_read_multiple(unsigned char reg, unsigned char * data, int length);




#endif