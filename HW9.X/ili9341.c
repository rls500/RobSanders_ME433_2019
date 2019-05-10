#include <xc.h>
#include "ili9341.h"

void LCD_init() {
    int time = 0;
    
    CSLCD = 0; // CS
   
    LCD_command(ILI9341_SWRESET);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 7200000) {} // 300ms

    LCD_command(0xEF);
  	LCD_data(0x03);
	LCD_data(0x80);
	LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCF);
  	LCD_data(0x00);
	LCD_data(0xC1);
	LCD_data(0x30);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xED);
  	LCD_data(0x64);
	LCD_data(0x03);
	LCD_data(0x12);
    LCD_data(0x81);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xE8);
  	LCD_data(0x85);
	LCD_data(0x00);
	LCD_data(0x78);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCB);
  	LCD_data(0x39);
	LCD_data(0x2C);
	LCD_data(0x00);
    LCD_data(0x34);
    LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF7);
  	LCD_data(0x20);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xEA);
  	LCD_data(0x00);
	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR1);
  	LCD_data(0x23);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR2);
  	LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR1 );
  	LCD_data(0x3e);
    LCD_data(0x28);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR2);
  	LCD_data(0x86);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_MADCTL);
  	LCD_data(0x48);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
/*    
    LCD_command(ILI9341_VSCRSADD);
  	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
 */   
    LCD_command(ILI9341_PIXFMT);
  	LCD_data(0x55);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_FRMCTR1);
  	LCD_data(0x00);
    LCD_data(0x18);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command( ILI9341_DFUNCTR);
  	LCD_data(0x08);
    LCD_data(0x82);
    LCD_data(0x27);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF2);
  	LCD_data(0); // 1
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GAMMASET);
  	LCD_data(0x01);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRP1);
  	LCD_data(0x0F);
    LCD_data(0x31);
    LCD_data(0x2B);
    LCD_data(0x0C);
    LCD_data(0x0E);
    LCD_data(0x08);
    LCD_data(0x4E);
    LCD_data(0xF1);
    LCD_data(0x37);
    LCD_data(0x07);
    LCD_data(0x10);
    LCD_data(0x03);
    LCD_data(0x0E);
    LCD_data(0x09);
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRN1);
  	LCD_data(0x00);
    LCD_data(0x0E);
    LCD_data(0x14);
    LCD_data(0x03);
    LCD_data(0x11);
    LCD_data(0x07);
    LCD_data(0x31);
    LCD_data(0xC1);
    LCD_data(0x48);
    LCD_data(0x08);
    LCD_data(0x0F);
    LCD_data(0x0C);
    LCD_data(0x31);
    LCD_data(0x36);
    LCD_data(0x0F);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xB1);
  	LCD_data(0x00);
    LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_SLPOUT);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_DISPON);
    
    CSLCD = 1; // CS
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    
    CSLCD = 0; // CS
    
    LCD_command(ILI9341_MADCTL);
    LCD_data(MADCTL_MX | MADCTL_BGR); // rotation
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    CSLCD = 1; // CS
}

void SPI1_init() {
  SDI1Rbits.SDI1R = 0b0100; // B8 is SDI1
  RPA1Rbits.RPA1R = 0b0011; // B11 is SDO1
  TRISBbits.TRISB7 = 0; // CSLCD is B7
  TRISBbits.TRISB9 = 0; // CSTOUCH is B9
  CSLCD = 1; // CS starts high
  CSTOUCH = 1;

  // DC pin
  TRISBbits.TRISB15 = 0;
  DC = 1;
  
  SPI1CON = 0; // turn off the spi module and reset it
  SPI1BUF; // clear the rx buffer by reading from it
  SPI1BRG = 3; // baud rate to 12 MHz [SPI1BRG = (48000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0; // clear the overflow bit
  SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
  SPI1CONbits.MSTEN = 1; // master operation
  SPI1CONbits.ON = 1; // turn on spi1
}

unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

void LCD_command(unsigned char com) {
    DC = 0; // DC
    spi_io(com);
    DC = 1; // DC
}

void LCD_data(unsigned char dat) {
    spi_io(dat);
}

void LCD_data16(unsigned short dat) {
    spi_io(dat>>8);
    spi_io(dat);
}

void LCD_setAddr(unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
    LCD_command(ILI9341_CASET); // Column
    LCD_data16(x);
	LCD_data16(x+w-1);

	LCD_command(ILI9341_PASET); // Page
	LCD_data16(y);
	LCD_data16(y+h-1);

	LCD_command(ILI9341_RAMWR); // Into RAM
}

void LCD_drawPixel(unsigned short x, unsigned short y, unsigned short color) {
  // check boundary
    
    CSLCD = 0; // CS
    
    LCD_setAddr(x,y,1,1);
    LCD_data16(color);
    
    CSLCD = 1; // CS
}

void LCD_clearScreen(unsigned short color) {
    int i;
    
    CSLCD = 0; // CS
    
    LCD_setAddr(0,0,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);
	for (i = 0;i < ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT; i++){
		LCD_data16(color);
	}
    
    CSLCD = 1; // CS
}

void LCD_drawLetter(char letter, unsigned short x, unsigned short y, unsigned short fontColor, unsigned short bckColor){
    int asciiRow = letter - 0x20;
    int j;
    int i;
    char bit;
    
    for(i=0; i<5; i++) { //loops through 5 columns to write
       for(j=0; j<8; j++) { //loops through 8 rows to write
           bit = ASCII[asciiRow][i] >> j & 1; //if the relevant bit is 1
           if(bit){
               LCD_drawPixel(x+i,y+j,fontColor);
           }
           else{
               LCD_drawPixel(x+i,y+j,bckColor);
           }
        } 
    }
    
}

void LCD_drawProgress(unsigned short x, unsigned short y, unsigned short length, unsigned short percentage, unsigned short barcolor, unsigned short bckcolor){
    int i;
    int j;
    
    for(i=0; i<length;i++) {
        for (j=0; j<8; j++){
            if (i < percentage){
                LCD_drawPixel(x+i,y+j,barcolor);
            }
            else{
                LCD_drawPixel(x+i,y+j,bckcolor);
            }
        }
    }
}
void LCD_drawString(char string[], unsigned short x, unsigned short y, unsigned short fontColor, unsigned short bckColor){
    int i=0;
    while(string[i]){
        LCD_drawLetter(string[i],x+i*5,y,fontColor,bckColor);
    i++;
    }

}
void Touch_read(unsigned short *x, unsigned short *y, unsigned int *z){
    
    unsigned char byte1;
    unsigned char byte2;
    unsigned int Z1;
    unsigned int Z2;
    
    CSTOUCH = 0;
    spi_io(0b10010001); 
    byte1 = spi_io(0x00);
    byte2= spi_io(0x00);
    CSTOUCH = 1;
    *y = ((byte1<<5) | (byte2>>3));

    
    CSTOUCH = 0;
    spi_io(0b11010001); 
    byte1 = spi_io(0x00);
    byte2= spi_io(0x00);
    CSTOUCH = 1;
    *x = (byte1<<5) | (byte2>>3);
    
    
    CSTOUCH = 0;
    spi_io(0b10110001); 
    byte1 = spi_io(0x00);
    byte2= spi_io(0x00);
    CSTOUCH = 1;
    Z1 = (byte1<<5) | (byte2>>3);
    
    CSTOUCH = 0;
    spi_io(0b11000001); 
    byte1 = spi_io(0x00);
    byte2= spi_io(0x00);
    CSTOUCH = 1;
    Z2 = (byte1<<5) | (byte2>>3);
    
    *z = Z1 - Z2 + 4095;
     
}

void Touch_Pix(unsigned short x,unsigned short y,unsigned short *xpix,unsigned short *ypix){
    //x: 290-3744
    //y: 95-3744
    *xpix = ((x-350)*240)/3744;
    *ypix= (((4095 -y)-95)*320)/3744 ;
         
}
void LCD_drawButton(unsigned short x, unsigned short y,unsigned short width, unsigned short height, char string[],unsigned short buttonColor){
    int i;
    int j;
    
    for(i=-width/2; i<width/2;i++) {
        for (j=-height/2; j<height/2; j++){
            LCD_drawPixel(x+i,y+j,buttonColor);
        }
    }
    LCD_drawString(string,x-5,y-2,ILI9341_WHITE,ILI9341_BLACK);
        
}
