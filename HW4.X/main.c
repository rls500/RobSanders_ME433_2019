#include <math.h> 	//for sine wave plotting
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "SPI.h"

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
#define CORE_TICKS 12000 // 24000 Ticks (1000 Hz)
#define VOLTAGE_MAX 4095 //12 bit range for DAC

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
    TRISAbits.TRISA4=0;
    
    
    LATAbits.LATA4=1;
    __builtin_enable_interrupts();
    
    init_SPI();
    
    int i =0;
    int v1=0;
    int rise=1;
    while(1){
        _CP0_SET_COUNT(0); //Start timer
        
        
        v1 = v1+rise*(VOLTAGE_MAX/(200/2)); //voltage increases or decreases proper 
        if((v1<=0) | (v1 >= VOLTAGE_MAX-100)){
            rise = rise*-1;
        }
        //Set triangle wave voltage
        setVoltage(0,v1);
        
        
        float f = VOLTAGE_MAX/2 +(VOLTAGE_MAX/2)*sin(i*2*3.1415/1000*10);  //should make a 10Hz sin wave)
        i++;
        
        setVoltage(1,f);
        
        while(_CP0_GET_COUNT()< 24000000/1000) {};
    }
}