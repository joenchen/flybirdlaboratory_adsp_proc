/*
==============================================================================

FILE:         HALclkBLSP1UART2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP1UART2 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP1UART2APPSClkDomain


   List of power domains:



==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8996/src/gcc/HALclkBLSP1UART2.c#1 $

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
06/16/2014           Auto-generated.


==============================================================================
            Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mBLSP1UART2APPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1UART2APPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_uart2_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_UART2_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_UART2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_UART2_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1UART2APPSClkDomain
 *
 * BLSP1UART2APPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART2APPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_UART2_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1UART2APPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1UART2APPSClkDomainClks)/sizeof(HAL_clk_mBLSP1UART2APPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

