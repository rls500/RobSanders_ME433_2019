/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    int CORE_TICKS = 12000;
    TRISAbits.TRISA4=0;
    TRISBbits.TRISB4=1;
    //SETS OUTPUT TO HIGH
    LATAbits.LATA4=1;
    
    
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            int CORE_TICKS = 1200000;
            int BAR_LENGTH = 100;
            char m[100];
            char recvd;
            int i;
            unsigned char data[14];
            signed short recondata[7];
            int accelPercent;

            recvd = IMU_read(WHOAMI);
            LCD_drawLetter(recvd,28,16,ILI9341_WHITE,ILI9341_BLACK);
            if(_CP0_GET_COUNT() >CORE_TICKS){
            LATAINV = 0b00010000;
            
            I2C_read_multiple(OUTX_L_XL, data, 6);
            IMU_reconstructData(data, recondata, 6);
     
            sprintf(m,"X: %i   ",recondata[0]);
            LCD_drawString(m,28,32+8*0,ILI9341_WHITE,ILI9341_BLACK);
            if (recondata[0]>0){
                accelPercent = (recondata[0])/163;
                LCD_drawXProgress(120,160,1,BAR_LENGTH,accelPercent,ILI9341_BLUE,ILI9341_WHITE);
                LCD_drawXProgress(120,160,-1,BAR_LENGTH,0,ILI9341_BLUE,ILI9341_WHITE);
            }
            else{
                accelPercent = (-recondata[0])/163;
                LCD_drawXProgress(120,160,-1,BAR_LENGTH,accelPercent,ILI9341_BLUE,ILI9341_WHITE);
                LCD_drawXProgress(120,160,1,BAR_LENGTH,0,ILI9341_BLUE,ILI9341_WHITE);
            }
            
            
            sprintf(m,"Y: %i   ",recondata[1]);
            LCD_drawString(m,28,32+8*1,ILI9341_WHITE,ILI9341_BLACK);
            if (recondata[1]>0){
                accelPercent = (recondata[1])/163;
                LCD_drawYProgress(120,160,1,BAR_LENGTH,accelPercent,ILI9341_BLUE,ILI9341_WHITE);
                LCD_drawYProgress(120,160,-1,BAR_LENGTH,0,ILI9341_BLUE,ILI9341_WHITE);
            }
            else{
                accelPercent = (-recondata[1])/163;
                LCD_drawYProgress(120,160,-1,BAR_LENGTH,accelPercent,ILI9341_BLUE,ILI9341_WHITE);
                LCD_drawYProgress(120,160,1,BAR_LENGTH,0,ILI9341_BLUE,ILI9341_WHITE);
            }
            
            _CP0_SET_COUNT(0);    
        }
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
