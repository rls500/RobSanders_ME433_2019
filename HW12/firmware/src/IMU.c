#include <xc.h>
#include "IMU.h"
#include "I2C.h"

void IMU_init(){
    i2c_master_start();                // Begin the start sequence
    i2c_master_send(IMU_ADDR << 1);    // send the slave address, left shifted by 1;
    i2c_master_send(CTRL1_XL);         // accelerometer register       
    i2c_master_send(0b10000010);       //1.66 kHZ, +/- 2g, 100 Hz Filter
    i2c_master_stop();
    
    i2c_master_start();                // Begin the start sequence
    i2c_master_send(IMU_ADDR << 1);    // send the slave address, left shifted by 1;
    i2c_master_send(CTRL2_G);          // gyro register       
    i2c_master_send(0b10001000);       //1.66 kHZ, 1000 dps sensitivity
    i2c_master_stop();
    
    i2c_master_start();                // Begin the start sequence
    i2c_master_send(IMU_ADDR << 1);    // send the slave address, left shifted by 1;
    i2c_master_send(CTRL3_C);          // cntrl1_xl register       
    i2c_master_send(0b00000100);       //1.66 kHZ, 1000 dps sensitivity
    i2c_master_stop();
    
}

unsigned char IMU_read(char reg){
    i2c_master_start();
    i2c_master_send(IMU_ADDR << 1);       // Begin the start sequence
    i2c_master_send(reg);
    i2c_master_restart();
    
    i2c_master_send((IMU_ADDR << 1)|1);       // send the slave address, left shifted by 1, ORed with 1 to indicate read
    unsigned char a = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return a;
}

void I2C_read_multiple(unsigned char reg, unsigned char * data, int length){
    int i;
    
    i2c_master_start();
    i2c_master_send(IMU_ADDR << 1);       // Begin the start sequence
    i2c_master_send(reg);
    i2c_master_restart();
    
    i2c_master_send((IMU_ADDR << 1)|1);       // send the slave address, left shifted by 1, ORed with 1 to indicate read
    
    for (i=0; i<length; i++){
        data[i] = i2c_master_recv();
    
        if(i==length-1){
            i2c_master_ack(1);
        }
        else{
            i2c_master_ack(0);
        }
    }
    
    i2c_master_stop();
    
}

void IMU_reconstructData(unsigned char * data, signed short * recondata, int length){
    int i;
    for(i=0;i<length;i=i+2){
        recondata[i/2] = data[i+1]<<8 | data[i];
    }
}

void LCD_drawXProgress(unsigned short x, unsigned short y,unsigned short dir, unsigned short length, unsigned short percentage, unsigned short barcolor, unsigned short bckcolor){
    int i;
    int j;
    
    for(i=0; i<length;i++) {
        for (j=0; j<8; j++){
            if (i < percentage){
                LCD_drawPixel(x+dir*i,y+j,barcolor);
            }
            else{
                LCD_drawPixel(x+dir*i,y+j,bckcolor);
            }
        }
    }
}

void LCD_drawYProgress(unsigned short x, unsigned short y,unsigned short dir, unsigned short length, unsigned short percentage, unsigned short barcolor, unsigned short bckcolor){
    int i;
    int j;
    
    for(i=0; i<length;i++) {
        for (j=0; j<8; j++){
            if (i < percentage){
                LCD_drawPixel(x+j,y+dir*i,barcolor);
            }
            else{
                LCD_drawPixel(x+j,y+dir*i,bckcolor);
            }
        }
    }
}