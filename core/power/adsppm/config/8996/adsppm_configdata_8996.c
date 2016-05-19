/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/


/*
 * adsspm_ConfigData.c - contains all 8996-specific data definitions for Config Manager
 *
 *  Created on: Sep 07, 2012
 *      Author: yrusakov/rli
 */
#include "adsppm.h"
#include "asic.h"
#include "asic_internal.h"
#include "adsppm_utils.h"
#include "icbid.h"
#include "DDIIPCInt.h"


/**
 * Array of 8996 Core Clocks per core. Arranged by to core ID
 */
const AdsppmClkIdType coreClocks_SlimBus_8996[] = {AdsppmClk_Slimbus_Core, AdsppmClk_Slimbus2_Core};
//const AdsppmClkIdType coreClocks_Midi_8996[]    = {AdsppmClk_Midi_Core};
const AdsppmClkIdType coreClocks_HwRsp_8996[]   = {AdsppmClk_HwRsp_Core};

/**
 * Array of 8996 Master Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType masterPorts_ADSP_8996[]    = {AdsppmBusPort_Adsp_Master};
const AdsppmBusPortIdType masterPorts_DML_8996[]     = {AdsppmBusPort_Dml_Master};
const AdsppmBusPortIdType masterPorts_AIF_8996[]     = {AdsppmBusPort_Aif_Master};
const AdsppmBusPortIdType masterPorts_SlimBus_8996[] = {AdsppmBusPort_Slimbus_Master, AdsppmBusPort_Slimbus2_Master};
//const AdsppmBusPortIdType masterPorts_Midi_8996[]    = {AdsppmBusPort_Midi_Master};
const AdsppmBusPortIdType masterPorts_HWRSMP_8996[]  = {AdsppmBusPort_HwRsmp_Master};
//const AdsppmBusPortIdType masterPorts_Spdif_8996[]   = {AdsppmBusPort_Spdif_Master};
const AdsppmBusPortIdType masterPorts_Hdmirx_8996[]  = {AdsppmBusPort_Hdmirx_Master};
//const AdsppmBusPortIdType masterPorts_Sif_8996[]     = {AdsppmBusPort_Sif_Master};

/**
 * Array of 8996 Slave Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType slavePorts_ADSP_8996[]    = {AdsppmBusPort_Adsp_Slave};
const AdsppmBusPortIdType slavePorts_LPM_8996[]     = {AdsppmBusPort_Lpm_Slave};
const AdsppmBusPortIdType slavePorts_DML_8996[]     = {AdsppmBusPort_Dml_Slave};
const AdsppmBusPortIdType slavePorts_AIF_8996[]     = {AdsppmBusPort_Aif_Slave};
const AdsppmBusPortIdType slavePorts_SlimBus_8996[] = {AdsppmBusPort_Slimbus_Slave, AdsppmBusPort_Slimbus2_Slave};
//const AdsppmBusPortIdType slavePorts_Midi_8996[]    = {AdsppmBusPort_Midi_Slave};
const AdsppmBusPortIdType slavePorts_AVsync_8996[]  = {AdsppmBusPort_AvSync_Slave};
const AdsppmBusPortIdType slavePorts_HWRSMP_8996[]  = {AdsppmBusPort_HwRsmp_Slave};
//const AdsppmBusPortIdType slavePorts_SRam_8996[]    = {AdsppmBusPort_Sram_Slave};
//const AdsppmBusPortIdType slavePorts_DCodec_8996[]  = {AdsppmBusPort_Dcodec_Slave};
//const AdsppmBusPortIdType slavePorts_Spdif_8996[]   = {AdsppmBusPort_Spdif_Slave};
const AdsppmBusPortIdType slavePorts_Hdmirx_8996[]  = {AdsppmBusPort_Hdmirx_Slave};
//const AdsppmBusPortIdType slavePorts_Sif_8996[]     = {AdsppmBusPort_Sif_Slave};
//const AdsppmBusPortIdType slavePorts_BSTC_8996[]    = {AdsppmBusPort_Bstc_Slave};

/**
 * Array of 8996 core descriptors. Arranged according to core ID enum
 */
const AsicCoreDescType cores_array_8996[] =
{
        {   //Adsppm_Core_Id_None
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_ADSP
                Adsppm_Core_Id_ADSP, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_ADSP, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_Adsp, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_ADSP_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_ADSP_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_LPM
                Adsppm_Core_Id_LPM, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Mem, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_LPM_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_DML
                Adsppm_Core_Id_DML, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_DML_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_DML_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_AIF
                Adsppm_Core_Id_AIF, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_AIF_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_AIF_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_SlimBus
                Adsppm_Core_Id_SlimBus, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {ADSPPM_ARRAY(coreClocks_SlimBus_8996)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_SlimBus_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_SlimBus_8996)}, //Slave port instances
                Adsppm_Instance_Id_1 //Number of core instances
        },
        {   //Adsppm_Core_Id_Midi
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_AVsync
                Adsppm_Core_Id_AVsync, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_AVsync_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_HWRSMP
                Adsppm_Core_Id_HWRSMP, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {ADSPPM_ARRAY(coreClocks_HwRsp_8996)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_HWRSMP_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_HWRSMP_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_SRam
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_DCodec
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Spdif
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Hdmirx
                Adsppm_Core_Id_Hdmirx, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_Hdmirx_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_Hdmirx_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_Sif
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_BSTC
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        }
};

AsicCoreDescriptorArrayType cores_8996 = {ADSPPM_ARRAY(cores_array_8996)};

const AsicMemDescriptorType memories_array_8996[] =
{
        {   //Adsppm_Mem_None
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
        {   //Adsppm_Mem_Ocmem
                Adsppm_Mem_Ocmem, //Mem ID
                AsicPowerDomain_Ocmem //Power Domain
        },
        {   //Adsppm_Mem_Lpass_LPM
                Adsppm_Mem_Lpass_LPM, //Mem ID
                AsicPowerDomain_Lpm //Power Domain
        },
        {   //Adsppm_Mem_Sram
                Adsppm_Mem_Sram, //Mem ID
                AsicPowerDomain_SRam //Power Domain
        }
};

AsicMemDescriptorArrayType memories_8996 = {ADSPPM_ARRAY(memories_array_8996)};

/**
 * Array of 8996 core clock descriptors. Arranged by core clock ID
 */
const AsicClkDescriptorType clocks_array_8996[] =
{
        {
                AdsppmClk_None, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Adsp_Core, //Clk ID
                AsicClk_TypeNpa, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "/clk/cpu", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Ahb_Root, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_core_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Adsp_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "q6ss_ahbm_aon_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Dml_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Aif_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Aif_Csr_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlAlwaysRetain, //MemCtrl Type
                "audio_core_aud_slimbus_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlAlwaysRetain, //MemCtrl Type
                "audio_core_qca_slimbus_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Midi_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lpm_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_lpm_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_Lpass_LPM //Memory ID
        },
        {
                AdsppmClk_Sram_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lcc_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbE_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbI_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {/* lcc clock for AHB2AXI bridge */
                AdsppmClk_AhbX_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_sysnoc_mport_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Csr_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Security_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Security_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Br_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Dcodec_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Spdif_Hmclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Spdif_Hsclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Smmu_Adsp_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Smmu_Lpass_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_peripheral_smmu_client_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sysnoc_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Hdmirx_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sif_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Bstc_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Core_AON, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Wrapper_AON, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_wrapper_aon_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_resampler_core_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Midi_Core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Xo, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Bt, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Fm, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_aud_slimbus_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_aud_slimbus_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Avtimer_core, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_avsync_stc_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atime_core, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "audio_core_avsync_atime_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atime2_core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        }
};

AsicClockDescriptorArrayType clocks_8996 = {ADSPPM_ARRAY(clocks_array_8996)};

/**
 * Arrays of 8996 register programming clocks
 */
const AdsppmClkIdType regProgClocks_Dml_8996[]      = {AdsppmClk_Dml_Hclk};
const AdsppmClkIdType regProgClocks_Aif_8996[]      = {AdsppmClk_Aif_Csr_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus_8996[]  = {AdsppmClk_Slimbus_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus2_8996[] = {AdsppmClk_Slimbus2_Hclk};
//const AdsppmClkIdType regProgClocks_Midi_8996[]     = {AdsppmClk_Midi_Hclk};
const AdsppmClkIdType regProgClocks_HwRsmp_8996[]   = {AdsppmClk_HwRsp_Hclk};
const AdsppmClkIdType regProgClocks_AvSync_8996[]   = {AdsppmClk_AvSync_Hclk};
const AdsppmClkIdType regProgClocks_Lpm_8996[]      = {AdsppmClk_Lpm_Hclk};
const AdsppmClkIdType regProgClocks_Sram_8996[]     = {AdsppmClk_Sram_Hclk};
//const AdsppmClkIdType regProgClocks_Spdif_8996[]    = {AdsppmClk_Spdif_Hsclk};
const AdsppmClkIdType regProgClocks_Hdmirx_8996[]   = {AdsppmClk_Hdmirx_Hclk};
//const AdsppmClkIdType regProgClocks_Sif_8996[]      = {AdsppmClk_Sif_Hclk};
//const AdsppmClkIdType regProgClocks_Bstc_8996[]     = {AdsppmClk_Bstc_Hclk};
//const AdsppmClkIdType regProgClocks_Dcodec_8996[]   = {AdsppmClk_Dcodec_Hclk};
const AdsppmClkIdType regProgClocks_Adsp_8996[]     = {AdsppmClk_Adsp_Hclk};

/**
 * Array of 8996 Bus port descriptors arranged by Bus port ID
 */
const AsicBusPortDescriptorType busPorts_array_8996[] =
{
        {
                AdsppmBusPort_None, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Adsp_Master, //ID
                AsicBusPort_AhbE_M | AsicBusPort_Ext_M,  //Connection
                AdsppmClk_Adsp_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_PROC}, //icbarb ID
                AdsppmBusPort_Adsp_Master //Access port
        },
        {
                AdsppmBusPort_Dml_Master, //ID
                AsicBusPort_AhbI_M | AsicBusPort_AhbX_M, //Connection
                AdsppmClk_Dml_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Aif_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Aif_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Slimbus_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Slimbus_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Slimbus2_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Midi_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_HwRsp_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //ID
                AsicBusPort_Ext_M, //Connection
                AdsppmClk_AhbX_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Spdif_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Hdmirx_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Hdmirx_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Sif_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Dml_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Dml_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Dml_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Aif_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Aif_Csr_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Aif_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Slimbus_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Slimbus2_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus2_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Midi_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_HwRsp_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_HwRsmp_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_AvSync_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_AvSync_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_AvSync_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Lpm_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Lpm_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Lpm_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Sram_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_AhbE_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Ddr_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Ocmem_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_OCMEM}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_PerifNoc_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_BLSP_1}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Spdif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Hdmirx_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Hdmirx_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Hdmirx_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Sif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Bstc_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Dcodec_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Core, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Adsp_Slave, //ID
                AsicBusPort_AhbE_S, //Connection
                AdsppmClk_Adsp_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Adsp_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Adsp_Master //Access port
        }
};

AsicBusPortDescriptorArrayType busPorts_8996 = {ADSPPM_ARRAY(busPorts_array_8996)};

/**
 * List of supported external bus routes
 */
const AdsppmBusRouteType extBusRoutes_array_8996[] =
{
        {
                AdsppmBusPort_Adsp_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        },
        {
                AdsppmBusPort_Adsp_Master, //master
                AdsppmBusPort_PerifNoc_Slave //slave
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        }
};

AsicBusRouteArrayType extBusRoutes_8996 = {ADSPPM_ARRAY(extBusRoutes_array_8996)};

const AdsppmBusRouteType mipsBwRoutes_array_8996[] =
{
        {
                AdsppmBusPort_Adsp_Master,
                AdsppmBusPort_Ddr_Slave
        }
};

AsicBusRouteArrayType mipsBwRoutes_8996 = {ADSPPM_ARRAY(mipsBwRoutes_array_8996)};

/**
* Array of register programming speeds in byte/sec
*/
const uint64 regProgSpeeds_array_8996[] =
{
        0,          //Adsppm_RegProg_None
        19200000*4, //Adsppm_RegProg_Norm
        61410000*4  //Adsppm_RegProg_Fast
};

AsicRegProgSpeedArrayType regProgSpeeds_8996 = {ADSPPM_ARRAY(regProgSpeeds_array_8996)};

/**
 * Array of power domain descriptors
 */
const AsicPowerDomainDescriptorType pwrDomains_array_8996[] =
{
        {
                AsicPowerDomain_AON, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Adsp, //Id
                "/core/cpu/latency", //Name
                AsicRsc_Power_ADSP, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_LpassCore, //Id
                "LPASS_AUDIO_CORE", //Name
                AsicRsc_Power_Core, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Lpm, //Id
                "", //Name
                AsicRsc_Power_Mem, //Type
                AdsppmClk_Lpm_Hclk, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_SRam, //Id
                "", //Name
                AsicRsc_Power_Mem, //Type
                AdsppmClk_Sram_Hclk, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Ocmem, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        }
};

AsicPwrDescriptorArrayType pwrDomains_8996 = {ADSPPM_ARRAY(pwrDomains_array_8996)};

const AsicFeatureDescType features_8996 [AsicFeatureId_enum_max] =
{
        //AsicFeatureId_Adsp_Clock_Scaling
        {
                AsicFeatureState_Enabled,
                80, //min MIPS
                905, //max MIPS
        },
        //AsicFeatureId_Adsp_LowTemp_Voltage_Restriction
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Adsp_PC
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Ahb_Scaling
        {
                AsicFeatureState_Enabled,
                76000000, //min bytes per second corresponds to 19Mhz clock
                614400000, //max bytes per second
        },
        //AsicFeatureId_Ahb_Sw_CG
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Ahb_DCG
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LpassCore_PC
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LpassCore_PC_TZ_Handshake
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Bus_Scaling
        {
                AsicFeatureState_Enabled,
                32768, //min bytes per second
                0x7FFFFFFF, //max bytes per second
        },
        //AsicFeatureId_CoreClk_Scaling
        {
                AsicFeatureState_Enabled,
                0, //min Hz
                153600000, //max Hz
        },
        //AsicFeatureId_Min_Adsp_BW_Vote
        {
                AsicFeatureState_Enabled,
                10000000, //min bytes per second
                0x7FFFFFFF, //max bytes per second
        },
        //AsicFeatureId_InitialState
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_TimelineOptimisationMips
        {
                AsicFeatureState_Disabled,
                240, //min MIPS for periodic clients
                905  //max MIPS value
        },
        //AsicFeatureId_TimelineOptimisationBw
        {
                AsicFeatureState_Disabled,
                76000000*8, //min ext BW in bytes per second (targeting above 76Mhz SNOC clk)
                0x7FFFFFFF, //max ext BW in bytes per second
        },
        //AsicFeatureId_TimelineOptimisationAhb
        {
                AsicFeatureState_Disabled,
                60000000, //min AHB clock in Hz
                153600000, //max AHB clock in Hz
        },
        //AsicFeatureId_LpassClkSleepOptimization
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LPMRetention
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        }
};
