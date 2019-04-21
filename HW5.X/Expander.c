#include "Expander.h"

void initExpander(){
    i2c_master_start();                     // Begin the start sequence
    i2c_master_send(SLAVE_ADDR << 1);       // send the slave address, left shifted by 1;
    //i2c_master_send(IOCON);
    //i2c_master_send(1<<5);
            
    i2c_master_send(IODIR);         // send a byte to the slave       
    i2c_master_send(0xf0);
    i2c_master_stop();
}

void setExpander(char pin, char level){
    i2c_master_start();                     // Begin the start sequence
    i2c_master_send(SLAVE_ADDR << 1);       // send the slave address, left shifted by 1;
    i2c_master_send(GPIO);         // send a byte to the slave       
    i2c_master_send(level << pin);
    i2c_master_stop();
}
unsigned char getExpander(){
    i2c_master_start();
    i2c_master_send(SLAVE_ADDR << 1);       // Begin the start sequence
    i2c_master_send(GPIO);
    i2c_master_restart();
    
    i2c_master_send((SLAVE_ADDR << 1)|1);       // send the slave address, left shifted by 1, ORed with 1 to indicate read
    unsigned char a = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return a;
}

