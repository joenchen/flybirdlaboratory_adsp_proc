/*
==============================================================================

FILE:         HALclkBLSP2QUP3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP2 QUP3 clocks.

   List of clock domains:
   -HAL_clk_mGCCBLSP2QUP3SPIClkDomain


==============================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/lpass_v1/src/gcc/HALclkBLSP2QUP3.c#1 $

when          who     what, where, why
--------      ---     ----------------------------------------------------------- 
10/31/2012            Auto-generated.

==============================================================================
            Copyright (c) 2012 Qualcomm Technologies Incorporated.
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


/* ============================================================================
**    Data
** ==========================================================================*/

                                    
/*                           
 *  HAL_clk_mBLSP2QUP3SPIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP2QUP3SPIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp2_qup3_spi_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP2_QUP3_SPI_APPS_CBCR), HWIO_OFFS(GCC_BLSP2_QUP3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP2_QUP3_SPI_APPS_CLK,
    /* .nChipsetFlag     = */ HAL_CLK_CHIP_FLAG_ALL & ~HAL_CLK_CHIP_FLAG_MDM9x25
  },
};


/*
 * HAL_clk_mGCCBLSP2QUP3SPIClkDomain
 *
 * BLSP2 QUP3 SPI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3SPIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP2_QUP3_SPI_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP2QUP3SPIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP2QUP3SPIClkDomainClks)/sizeof(HAL_clk_mBLSP2QUP3SPIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


