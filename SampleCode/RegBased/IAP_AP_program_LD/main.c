/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

#define     DATA_START_ADDR     0x0000

void main (void) 
{
    unsigned char i;

    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    
    for (i=0;i<128;i++)
        IAPDataBuf[i]=i;

    while(P05);

    Erase_LDROM(DATA_START_ADDR,128);
    Erase_Verify_LDROM(DATA_START_ADDR,128);
    Program_LDROM(DATA_START_ADDR,128);
    Program_Verify_LDROM(DATA_START_ADDR,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
