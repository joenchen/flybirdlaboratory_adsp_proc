/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * @file requestmgr.h
 * @brief request manager header file
 *
 * This file include type definition for request manager, it's used inside adsppm.
 *  Created on: Feb 13, 2012
 *      Author: alisonc
 */

#ifndef REQUESTMGR_H_
#define REQUESTMGR_H_

#include "adsppm.h"
#include "coreUtils.h"


/**
 * @enum RMValidFlagType - ADSPPM Request manager table valid status
 */
typedef enum{
    RM_InValid                = 0,
    RM_Valid                  = 1,
    RM_Suspended              = 2,
    RM_Valid_Flag_Force32Bits = 0x7FFFFFFF //!< forcing enum to be 32 bit
} RMValidFlagType;

/**
 * @struct RMHandleType - request manager context used to hold information for client and resource
 */
typedef struct{
    coreUtils_Q_LinkType rmHandleQLink;     //!< link to next element in list/queue
    RMValidFlagType      validFlag;         //!< Flag showing whether request data is valid
    RMValidFlagType      validFlag_Ext;     //!< Flag showing whether extended request data is valid
    uint32               clientId;
    AdsppmRscIdType      rmRscId;
    AdsppmHandleType     *pAdsppmHandle;    //!< Pointer to client adsppm handle in gAdsppmCoreCtx->adsppmHandleQ
    void                 *pRequestData;     //!< Pointer to request data
    void                 *pRequestData_Ext; //!< Pointer to request data extension if required
} RMHandleType;


/**
 * @fn RM_Init - init RM, create resource mutex
 * @return Adsppm_Status
 */
Adsppm_Status RM_Init(void);


#endif /* REQUESTMGR_H_ */
