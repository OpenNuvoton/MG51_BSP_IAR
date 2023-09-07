/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

unsigned char  UART_BUFFER;

#pragma vector=0x7B
__interrupt void SerialPort1_ISR(void){
    PUSH_SFRS;
  
    if (RI_1)
    {
        uart1_receive_data = SBUF_1;
        uart1_receive_flag = 1;
        clr_SCON_1_RI_1;                             /* clear reception flag for next reception */
    }

    if (TI_1 == 1)
    {
        if (!PRINTFG)
        {
            clr_SCON_1_TI_1;                             /* if emission occur */
        }
    }

    POP_SFRS;
}
/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
  
 !!! UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.

 External UART1 connect also disturb debug download

 ***************************************************************************************************************/
void main (void)
{
    GPIO_LED_QUASI_MODE;    // For I/O toggle display
/* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf(" \n\r Please remove Nu-link or not in debug mode to test UART1 function.  \n\r");
    
    P16_QUASI_MODE;
    P02_INPUT_MODE;
    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;                //ENABLE_GLOBAL_INTERRUPT

    while(1)
    {
      if (uart1_receive_flag)
      {
          GPIO_LED ^= 1;      //Receive each byte GPIO_LED toggle, never work under debug mode
          UART_Send_Data(UART1,uart1_receive_data);
          uart1_receive_flag = 0;
      }
    }
}
  
