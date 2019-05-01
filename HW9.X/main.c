#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "I2C.h"
#include "ili9341.h"


// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable secondary osc
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1 // use slowest wdt
#pragma config WINDIS = OFF // wdt no window mode
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt  window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0x0fab // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module

//Constants
#define CORE_TICKS 1200000
#define BAR_LENGTH 100



int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    //0 sets as input, 1 as output
    TRISAbits.TRISA4=0;
    TRISBbits.TRISB4=1;
    //SETS OUTPUT TO HIGH
    LATAbits.LATA4=1;
    
    i2c_master_setup();
    SPI1_init();
    LCD_init();
    LCD_clearScreen(ILI9341_PINK);
    __builtin_enable_interrupts();
    
    unsigned short x, y; int z;
    unsigned short xpix, ypix;
    char xval[20];
    char yval[20];
    char zval[20];
    char m[100];
    char plus[20]="I++";
    char minus[20]="I--";
    unsigned short buttonWidth = 80;
    unsigned short buttonHeight = 50; 
    unsigned short buttonCenterX = 175;
    unsigned short plusCenterY = 100;
    unsigned short minusCenterY=200;
    int I=0;
    
    LCD_drawButton(buttonCenterX,plusCenterY,buttonWidth,buttonHeight,plus,ILI9341_BLACK);
    LCD_drawButton(buttonCenterX,minusCenterY,buttonWidth,buttonHeight,minus,ILI9341_BLACK);
    
    while(1){
        _CP0_SET_COUNT(0);
       
       Touch_read(&x, &y, &z);
       Touch_Pix(x,y,&xpix,&ypix);
       sprintf(xval,"X: %d     ",xpix);
       LCD_drawString(xval,28,32,ILI9341_BLACK,ILI9341_PINK);
       sprintf(yval,"Y: %d     ",ypix);
       LCD_drawString(yval,28,32+8*1,ILI9341_BLACK,ILI9341_PINK);
       sprintf(zval,"Z: %d     ",z);
       LCD_drawString(zval,28,32+8*2,ILI9341_BLACK,ILI9341_PINK);
       
       if(z>1700){
           sprintf(xval,"(X,Y): %d,%d     ",xpix,ypix);
           LCD_drawString(xval,28,300,ILI9341_BLACK,ILI9341_PINK);
           
           if(xpix > buttonCenterX - buttonWidth/2 & xpix < buttonCenterX+buttonWidth/2 & ypix > plusCenterY-buttonHeight/2 & ypix < plusCenterY+buttonHeight/2 ){
               while(z>1700){
                   Touch_read(&x, &y, &z);
               }
               I++;
            }
            else if (xpix > buttonCenterX - buttonWidth/2 & xpix < buttonCenterX+buttonWidth/2 & ypix > minusCenterY-buttonHeight/2 & ypix < minusCenterY+buttonHeight/2 ){
                while(z>1700){
                   Touch_read(&x, &y, &z);
               }
                I--;
            }
            
        }
       else{
           sprintf(xval,"(X,Y):           ",xpix,ypix);
           LCD_drawString(xval,28,300,ILI9341_BLACK,ILI9341_PINK);
       }
       sprintf(m,"  I = %d  ",I);
       LCD_drawString(m,buttonCenterX - 15,(plusCenterY+minusCenterY)/2,ILI9341_WHITE,ILI9341_BLACK);
       
    
    
    
    }  
}