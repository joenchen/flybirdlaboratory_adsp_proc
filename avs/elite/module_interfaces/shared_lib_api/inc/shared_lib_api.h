#ifndef SHARED_LIB_API_H
#define SHARED_LIB_API_H

/* ========================================================================*/
/**
 @file shared_lib_api.h
 Contains APIs exposed to the shared libraries

   This file contains the C APIs that are exposed to the shared libraries used
   for dynamic loading.

 */

/*======================================================================
 Copyright (c) 2014 QUALCOMM Technologies Incorporated.
 All rights reserved. Qualcomm Proprietary and Confidential.
 ====================================================================== */

/* =========================================================================
 Edit History

 when       who         what, where, why
 --------   -------     ------------------------------------------------------
 08/29/14   rbhatnk     Created file.
 ========================================================================= */

/** *
 * Guidelines:
 * 1. All the APIs that a module shares with the DSP have to be captured here.
 *    This includes APR APIs as well if modules are referring to them.
 * 2. APIs mentioned here need to be backward compatible. This includes everything: macros, constants, functions, structures, ...
 *    Exceptions:
 *     2a. If an API is needed to be included here, but is not used by shared libraries (see qurt_elite_diag.h below)
 *     2b. functions: all functions exposed in shared_lib_api_export.lst need to be backward compatible. But others need not be.
 *
 * 3. Any change in APIs need to increment minor/major version.
 */

/**
 * Major version of the shared library API.
 *
 * Incremented by one whenever backward compatibility is broken.
 *
 */
#define SHARED_LIB_API__API_MAJOR_VERSION              1

/**
 * Minor version of the shared library API.
 *
 * Incremented by one for backward compatible changes.
 */
#define SHARED_LIB_API__API_MINOR_VERSION              0

/** Basic types */
#include "mmdefs.h"

/** Error codes */
#include "adsp_error_codes.h"

/** Qurt */
#include "qurt.h"

/** Subset of APIs from Qurt Elite */
#include "filtered_qurt_elite.h"

/** License DB APIs */
#include "adsp_license_db.h"

/** CAPI and APPI */
#include "Elite_CAPI_V2.h"
#include "Elite_APPI.h"
#include "Elite_CAPI.h"
#include "Elite_CAPI_V2_private_params.h"
#include "Elite_fwk_extns_feedback.h"

/** Elite ADSP APR APIs */
#include "adsp_media_fmt.h"
#include "adsp_asm_stream_commands.h"

#include <stringl.h>

#ifdef AVS_BUILD_SOS
/** MSG to FARF converter & Diag utilities needed only for .so files.*/
#include "HAP_diag.h"

#else // !AVS_BUILD_SOS
/** these includes don't need to be backward compatible as
 * these are not exposed to shared libraries.*/

#include "qurt_elite_diag.h"

#endif //AVS_BUILD_SOS

/** Audio common Ops, math utils */
#include "shared_aud_cmn_lib.h"
#include "Interleaver.h"

#define SHARED_LIB_API__SHARED_LIB_BUILD_PROPERTY_VERSION 0x1

/** Structure of build property of ADSP builds for version 1. */
typedef struct adsp_avs_build_property_t
{
   uint16_t build_property_version;
      /**< version of this struct. Supported values: any. */
   uint16_t api_major_version;
      /**< Major version of the shared library API. Supported values: any.*/
   uint16_t api_minor_version;
      /**< Minor version of the shared library API. Supported values: any. */
   uint16_t qurt_api_version;
      /**< Qurt API version. Supported values: any. */
   uint32_t hexagon_tools_version;
      /**< Hexagon tools version xx.yy.zz is represented as uint32_t 00xxyyzz, where xx, yy, and zz are decimals.
       *    Supported values: any. */
} adsp_avs_build_property_t;

#define SHARED_LIB_API__ADSP_BUILD_PROPERTY_VERSION 0x1

/** Maximum characters in the shared library's BUILD_ID string.*/
#define SHARED_LIB_API__MAX_CHARS_IN_SHARED_LIB_BUILD_ID       128

/** Structure of build property of shared library builds for version 1. */
typedef struct shared_lib_build_property_t
{
   uint16_t build_property_version;
      /**< version of this struct. Supported values: any. */
   uint16_t api_major_version;
      /**< Major version of the shared library API. Supported values: any.*/
   uint16_t api_minor_version;
      /**< Minor version of the shared library API. Supported values: any. */
   uint16_t lib_major_version;
      /**< Major version of the shared library. Supported values: any. */
   uint16_t lib_minor_version;
      /**< Minor version of the shared library. Supported values: any. */
   uint16_t is_qurt_used;
      /**< Is qurt used in the shared library. Supported values: any. zero => FALSE, nonzero => TRUE */
   uint16_t qurt_api_version;
      /**< Qurt API version. Must be checked only if is_qurt_used is nonzero. */
   uint16_t reserved;
      /**< reserved field must be set to zero. used for 32bit alignment */
   uint32_t hexagon_tools_version;
      /**< Hexagon tools version : xx.yy.zz is represented as uint32_t 00xxyyzz, where xx, yy, and zz are decimals.*/
   uint8_t  build_id[SHARED_LIB_API__MAX_CHARS_IN_SHARED_LIB_BUILD_ID];
      /**< BUILD ID string containing major and minor versions of the library along with time-stamp of build. */

} shared_lib_build_property_t;

/**
 * Build property string for symbol lookup
 */
#define SHARED_LIB_API__SHARED_LIB_BUILD_PROPERTY_STRING "shared_lib_build_property"
/**
 * Build property string for symbol lookup
 */
#define SHARED_LIB_API__ADSP_AVS_BUILD_PROPERTY_STRING "adsp_avs_build_property"

#ifdef AVS_BUILD_SOS //for shared libraries

extern const shared_lib_build_property_t shared_lib_build_property;

#else //AVS_BUILD_SOS, for main ADSP build

extern const adsp_avs_build_property_t adsp_avs_build_property;

#endif //AVS_BUILD_SOS

#endif //SHARED_LIB_API_H
