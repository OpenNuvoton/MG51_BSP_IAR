/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

void main(void)
{
  P11_PUSHPULL_MODE;
  GPIO_LED_QUASI_MODE;
  set_CKCON_CLOEN;
/* clock out div 100 */
  CKDIV = 50;
  while (P20)
  {
    MODIFY_HIRC(HIRC_16);
    GPIO_LED = 1;
    Timer0_Delay(16000000,5,1000);
    GPIO_LED = 0;
    Timer0_Delay(16000000,5,1000);
  }
/* HIRC modify to 24MHz  */
  MODIFY_HIRC(HIRC_24);
  while(1);
  
}