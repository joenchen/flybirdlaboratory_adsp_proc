/*==============================================================================
   FILE:        MPMIntDevCfgData.c

  OVERVIEW:     MPM hardware to local interrupt/gpio mapping info. This
                mapping is target specific and may change for different 
                targets. Even mapping could change between masters within a
                same target as some master may want a mapped irq as wakeup
                interrupt while other may not.
 
  DEPENDENCIES: None

                Copyright (c) 2013 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/config/asic/8994/MPMIntDevCfgData.c#1 $
$DateTime: 2014/10/16 12:45:40 $
=============================================================================*/ 

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "vmpm_internal.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/**
 * Table mapping the MPM Pin number to the GPIO and/or IRQ pin 
 * number per the IP Catalog. 
 */
mpm_int_pin_mapping_type devcfg_MpmInterruptPinNum_Mapping[] =
{
  /* Trigger                 Local Pin#         Pin Type   */
  /* -------                 -------------      --------   */
  /*0*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 101             , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 1               , MPM_GPIO },
  /*5*/
  { MPM_TRIGGER_RISING_EDGE, 5               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 9               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 18              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 22              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 26              , MPM_GPIO },
  /*10*/
  { MPM_TRIGGER_RISING_EDGE, 29              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 34              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 36              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 37              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 41              , MPM_GPIO },
  /*15*/
  { MPM_TRIGGER_RISING_EDGE, 42              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 46              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 50              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 52              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 53              , MPM_GPIO },
  /*20*/
  { MPM_TRIGGER_RISING_EDGE, 54              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 55              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 57              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 40              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 61              , MPM_GPIO },
  /*25*/
  { MPM_TRIGGER_RISING_EDGE, 64              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 65              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 66              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 67              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 72              , MPM_GPIO },
  /*30*/
  { MPM_TRIGGER_RISING_EDGE, 73              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 74              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 75              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 76              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 77              , MPM_GPIO },
  /*35*/
  { MPM_TRIGGER_RISING_EDGE, 82              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 86              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 90              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 95              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 96              , MPM_GPIO },
  /*40*/
  { MPM_TRIGGER_RISING_EDGE, 100             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  71              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 108             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  111             , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  115             , MPM_GPIO },
  /*45*/
  { MPM_TRIGGER_LEVEL_HIGH,  127             , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  /*50*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  /*55*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  /*60*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  /*64 - End of the table entry */
  { MPM_TRIGGER_LEVEL_HIGH,      MPM_UNMAPPED_INT, MPM_EOT  },
};
