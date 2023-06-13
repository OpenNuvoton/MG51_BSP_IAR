/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 read UCID demo
//***********************************************************************************************************
#include "MG51_IAR.H"


void main(void)
{
  unsigned char ct;
  
/* Modify HIRC to 24MHz for UART printf function only */
  MODIFY_HIRC(HIRC_24);
  Enable_UART0_VCOM_printf_24M_115200();

  Read_UCID();
  printf ("\n\r UCID = ");
  for(ct=0;ct<12;ct++)
  {
    printf (" 0x%X \r",UCIDBuffer[ct]);
  }

  while(1);


}