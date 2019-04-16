// PIC is the master, ram is the slave
// Uses microchip 23K256 ram chip (see the data sheet for protocol details)
// SDO1 -> SI (pin B13 -> pin 5) 0011
// SDI1 -> SO (pin B11 -> pin 2) 0011
// SCK1 -> SCK (pin B14 -> pin 6)
// SS1 -> CS (pin B15 -> pin 1) 0011
// Additional SRAM connections
// Vss (Pin 4) -> ground
// Vcc (Pin 8) -> 3.3 V
// Hold (pin 7) -> 3.3 V (we don't use the hold function)

#define CS LATBbits.LATB15

char spi_io(char write){
    SPI1BUF = write;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

void setVoltage(char channel, int voltage) {
    unsigned short t = 0;
	t= channel << 15;         //channel is at the very end of the data transfer
	t = t | 0b01110000000000000;
	t = t | ((voltage&0b111111111111)); //rejecting excessive bits (above 10)
	
	CS = 0;
	spi_io(t >>8);
	spi_io((t & 0b11111111));
    CS = 1;
}

void init_SPI(){
    
    RPB13Rbits.RPB13R = 0b0011; //Tie B13 to SDO1
    SDI1Rbits.SDI1R = 0b0011;   //Tie SDI1 to B11
    RPB15Rbits.RPB15R = 0b0011; //Tie B15 to SS1
    
    TRISBbits.TRISB15 = 0;
    CS = 1;
    
    SPI1CON = 0;              // turn off the spi module and reset it
    SPI1BUF;                  // clear the rx buffer by reading from it
    SPI1BRG = 0x2;            // baud rate to 10 MHz [SPI4BRG = (80000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1;    // master operation
    SPI1CONbits.ON = 1;       // turn on spi 1
}
