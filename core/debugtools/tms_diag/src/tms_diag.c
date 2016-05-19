/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Defnitions for diagpkts used by various TMS modules

GENERAL DESCRIPTION
  Common internal defniitions for diag command handling by TMS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  No requirements

Copyright (c) 2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.adsp/2.6.1/debugtools/tms_diag/src/tms_diag.c#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
09/22/14   dav     File created.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "tms_diag.h"

diagpkt_user_table_entry_type tms_diag_build_table_entry(CMD cmd, void* cb){
  diagpkt_user_table_entry_type diagpkt;
  DALSYSPropertyVar propValue;
  DALSYS_PROPERTY_HANDLE_DECLARE(pHandle);

  DALSYS_GetDALPropertyHandleStr("tms_diag",pHandle);

  // Check Image ID
  if (DAL_SUCCESS == DALSYS_GetPropertyValue(pHandle,"image_id", 0, &propValue))
  {
    diagpkt.cmd_code_lo = (propValue.Val.dwVal<<8)+cmd;
    diagpkt.cmd_code_hi = (propValue.Val.dwVal<<8)+cmd;
	diagpkt.func_ptr = cb;
	return diagpkt;
  }
  else
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Could not read image_id devcfg");
	return diagpkt;
  }
}

diagpkt_user_table_entry_type tms_diag_build_table_entry_uimg(CMD cmd, void* cb){
  diagpkt_user_table_entry_type diagpkt;
  DALSYSPropertyVar propValue;
  DALSYS_PROPERTY_HANDLE_DECLARE(pHandle);

  DALSYS_GetDALPropertyHandleStr("tms_diag",pHandle);

  // Check Image ID
  if (DAL_SUCCESS == DALSYS_GetPropertyValue(pHandle,"image_id", 0, &propValue))
  {
    diagpkt.cmd_code_lo = ( (propValue.Val.dwVal+1)<<8 )+cmd;
    diagpkt.cmd_code_hi = ( (propValue.Val.dwVal+1)<<8 )+cmd;
	diagpkt.func_ptr = cb;
	return diagpkt;
  }
  else
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Could not read image_id devcfg");
	return diagpkt;
  }
}


void tms_diag_send_generic_response (void * req)
{
  void * rsp = NULL;

  /* build response */
  rsp = diagpkt_subsys_alloc(
     diagpkt_subsys_get_id(req),                       
     diagpkt_subsys_get_cmd_code(req), 
     sizeof( diagpkt_subsys_header_type ));

  // send response 
  diagpkt_commit(rsp);

}
