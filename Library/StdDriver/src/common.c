/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"

BIT BIT_TMP;
/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr)
{
    unsigned char rdata;
    rdata = *u16_addr >> 8;
    return rdata;
}

/**
 * @brief       Software reset API
 * @param       Run in APROM/LDROM after reset
 *                       - \ref BOOT_APROM: Run in APROM after reset .
 *                       - \ref BOOT_LDROM: Run in LDROM after reset.
 * @return      None
 * @details     None
 */
void Software_Reset(unsigned char u8Bootarea)
{
    unsigned char boottemp;
    boottemp = (0x80|u8Bootarea);
    TA = 0xAA;
    TA = 0x55;
    CHPCON = boottemp;                   //software reset enable
}

/**
 * @brief       MCU power down mode enable API
 * @param       Enable power down mode
 *                       - \ref ENABLE: Run into power down mode .
 * @return      None
 * @details     None
 */
void PowerDown_Mode(unsigned char PDStatus)
{
    if (PDStatus==1)
    {
       POWERDOWN_MODE_ENABLE;
       CALL_NOP;
       CALL_NOP;
    }
}

/**
 * @brief       MCU idle mode enable API
 * @param       Enable idle mode
 *                       - \ref ENABLE: Run into idle mode .
 * @return      None
 * @details     None
 */
void Idle_Mode(unsigned char IdleStatus)
{
    if (IdleStatus==1)
    {
       IDLE_MODE_ENABLE;
       CALL_NOP;
       CALL_NOP;
    }
}

/**
 * @brief       Loop delay  
 * @param       None
 * @return      None
 * @details     None
**/
void _delay_(void)
{
  unsigned char ui,uj;
    for (uj=0;uj<0x1A;uj++)
    {
       for (ui=0;ui<0xff;ui++)
       {
          CALL_NOP;
       }
    }
}  