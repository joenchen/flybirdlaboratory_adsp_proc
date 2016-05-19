#ifndef SNS_RH_SOL_H
#define SNS_RH_SOL_H

/*============================================================================

  @file sns_rh_sol.h

  @brief
  This file contains definition used in managing the Standing Orders List (SOL) of
  the Request Handler task

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_sol.h#3 $ */
/* $DateTime: 2015/05/07 16:02:28 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-01-13  pn   Fixed Flush command handling
  2014-12-03  pn   Handles report replacement for Periodic reports
  2014-11-06  pn   Added macro RH_FOR_EACH_REPORT_ITEM()
  2014-10-24  jms  Rpt sending with effective_rate_hz=0 fix
  2014-10-22  pn   Added event_sensors_only flag to reports
  2014-10-15  rt   Added 'deleting' state to reports
  2014-10-02  pn   Added sns_rh_update_periodic_like_flag()
  2014-09-25  pn   Selects appropriate depot for report item
  2014-09-16  pn   Added holding queue needed to track event gated reports
  2014-08-05  pn   Added more report states
  2014-06-16  pn   Reduced unnecessary updates to report info
  2014-06-16  pn   Removed references to unused circular buffer
  2014-05-12  tc   Converted frequencies to fixed point, Q16. This is to
                   accommodate frequencies less than 1. Q16 fixed point is
                   used, instead of floating point, because the Q6 does not
                   have hardware-support for floating point division.
  2014-04-23  pn   Initial version
============================================================================*/
#include "sns_smgr_depot.h"
#include "sns_rh.h"
#include "sns_rh_mr.h"
#include "sns_rh_sample_proc_uimg.h"

/*===========================================================================

                   MACROS

===========================================================================*/
#ifndef SNS_SMGR_DEBUG
#define RH_UPDATE_INTERP_TIMESTAMP(iobj) \
  ( (iobj)->desired_timestamp = \
      ((iobj)->interval_ticks != 0) ? \
      (((iobj)->desired_timestamp + (iobj)->interval_ticks)/ (iobj)->interval_ticks*(iobj)->interval_ticks) : \
      (iobj)->desired_timestamp )
#else
#define RH_UPDATE_INTERP_TIMESTAMP(iobj) \
do { \
  ( (iobj)->desired_timestamp = \
      ((iobj)->interval_ticks != 0) ? \
      (((iobj)->desired_timestamp + (iobj)->interval_ticks)/ (iobj)->interval_ticks*(iobj)->interval_ticks) : \
      (iobj)->desired_timestamp ); \
   SNS_SMGR_PRINTF2(LOW, "desiredTS = %d, obj=0x%x", (iobj)->desired_timestamp, (iobj)); \
} while ( 0 );
#endif

#define RH_FOR_EACH_REPORT_ITEM(rp,i) \
  for ( i=0; i<(rp)->num_items && i<ARR_SIZE((rp)->item_list); i++ )

/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/
/* bits assigned to smgr_rpt_item_s.flags */
#define RH_RPT_ITEM_FLAGS_DECIM_FILTER_B    0x01
#define RH_RPT_ITEM_FLAGS_ACCURATE_TS_B     0x02

typedef enum
{
  RH_RPT_ITEM_STATE_LINKING,    /* being added */
  RH_RPT_ITEM_STATE_UNLINKING,  /* being removed */
  RH_RPT_ITEM_STATE_IDLE,       /* after initialization or after send the report */
  RH_RPT_ITEM_STATE_PENDING,
  RH_RPT_ITEM_STATE_DONE,       /* sample available */
} rh_rpt_item_status_e;

typedef enum
{
  RH_RPT_STATE_ACTIVE,            /* default */
  RH_RPT_STATE_FLUSHING,          /* unscheduled report due to ODR(s) change */
  RH_RPT_STATE_FIFO_FLUSH_PENDING,/* waiting for FIFO_FLUSHED_SIG */
  RH_RPT_STATE_FIFO_FLUSH_READY,  /* ready for FIFO_FLUSHED_SIG */
  RH_RPT_STATE_INACTIVE,          /* maybe due to self-test */
  RH_RPT_STATE_DELETING           /* in the process of being deleted */
} rh_rpt_state_e;


typedef enum
{
  RH_RPT_STATE_EXT_NONE,            /*0 default */
  RH_RPT_STATE_EXT_FLUSH_AND_DELETE_PENDING, /*1 delete when fifo & depot flush is done */
  RH_RPT_STATE_EXT_RESP_PENDING,    /*2 send response when starts reporting or fails */
} rh_rpt_state_ext_e;

/*===========================================================================

                   STRUCTURE DEFINITIONS

===========================================================================*/

/*  =============== Query structure ===============
    Contains data to define and manage an outstanding Buffering Query.
    A client adds a Buffering report with report rate of 0Hz then follows that
    by a series of Buffering Query requests.  Each Buffering Query request
    will have one corresponding response and one corresponding indication.
*/
struct sns_rh_query_s
{
  sns_rh_query_s*           next_query_ptr;
  sns_rh_rpt_item_s*        item_ptr;
  sns_rh_mr_header_s        msg_header;
  uint16_t                  query_id;
  uint32_t                  T0;
  uint32_t                  T1;
  bool                      ready;
};

struct sns_rh_rpt_item_s
{
  sns_rh_rpt_item_s*            next_item_ptr;

  sns_smgr_ddf_sensor_s*        ddf_sensor_ptr;

  sns_smgr_sample_depot_s*      depot_ptr;

  /* the report to which this item belongs */
  sns_rh_rpt_spec_s*            parent_report_ptr;

  /* list of outstanding Buffering Query */
  sns_rh_query_s*               query_ptr;

  /* the status such as if the sensor value have been read or pending */
  rh_rpt_item_status_e          state;

  /* See definitions for RH_RPT_ITEM_FLAGS_... */
  uint8_t                       flags;

  bool                          rate_thresholds_met;
  bool                          samples_sent;

  uint8_t                       quality;

  q16_t                         sampling_rate_hz; //todo SMGR_SUBHZ
  uint32_t                      sampling_interval;
  uint8_t                       sampling_factor;
  uint8_t                       sampling_count;
  uint16_t                      num_samples; /* number of samples expected for sampling_interval */
  q16_t                         effective_rate_hz;
  uint32_t                      last_processed_sample_timestamp;

  /* keeps track of timestamp of latest sample in previous indication to
     prevent sending old samples */
  sns_ddf_time_t                ts_last_sent;

  uint8_t                       sensitivity;     /* This item's sensor sensitivity parameter.
                                                    =0 for default or 1-100 for lowest to highest sensitivity */
  sns_rh_cic_obj_s              cic_obj;
  sns_rh_interpolator_obj_s     interpolator_obj;
  sns_smgr_sample_s             resulting_sample;

  sns_smgr_sample_depot_iter_s  depot_iter;
  uint8_t                       cal_sel;  /* see define SNS_SMGR_CAL_SEL_XXX */
};     

struct sns_rh_rpt_spec_s
{
  /* Link to report_queue */ 
  sns_q_link_s                  rpt_link;

  /* Reports ready to be sent are added to singly-linked list */
  sns_rh_rpt_spec_s*            next_ready_report_ptr;

  /* list of items belonging to this report */
  sns_rh_rpt_item_s*            item_list[SNS_SMGR_MAX_ITEMS_PER_REPORT_V01];
  uint8_t                       num_items;

  /* Information from request message header */
  sns_rh_mr_header_s            msg_header;

  rh_rpt_state_e                state;

  rh_rpt_state_ext_e            state_extended; /* state extension (sub states) */
  sns_rh_rpt_spec_s*            pending_rpt_ptr;
  /*rpt with rpt_id that already exists. New rpt activation after existing is deleted*/
  sns_common_resp_s_v01*        resp_ptr;    /* conf for pending response */
  sns_rh_mr_header_s            mr_hdr;         /* conf for pending response */

  /* Report ID is defined by the client to distinguish the client's
     various reports, 0-255 */
  uint8_t                       rpt_id;
  
  q16_t                         q16_rpt_rate;
  uint32_t                      rpt_interval; /* time ticks between indications */
  uint32_t                      rpt_tick; /* time tick at which to send indication */
  uint32_t                      min_sampling_interval;
  sns_ddf_time_t                ts_last_rpt_sent;
  sns_ddf_time_t                ts_last_updated;

  /* Counts number of indications sent for this report ID.
     For informational only as count can rollover */
  uint32_t                      ind_count;

  /* processor on which this report originated */
  uint32_t                      proc_type;

  bool                          send_ind_during_suspend; 
  bool                          periodic_like; /* when report rate == all sampling rates */
  bool                          event_sensors_only; /* no streaming sensors requested */

  /* Sensor Event's queues for conditioned reports to which this report might belong */
  sns_q_s*                      sensor_event_q;
};


/*===========================================================================

                          FUNCTIONS

===========================================================================*/
extern q16_t smgr_rate_hz_to_q16(uint16_t rate);

extern uint8_t sns_rh_sol_parse_item_decimation(
  uint8_t             decimation,
  sns_rh_rpt_item_s*  item_ptr);

extern bool sns_rh_sol_parse_buffering_item(
  uint8_t                                  item_idx,
  const sns_smgr_buffering_req_item_s_v01* in_item_ptr,
  sns_rh_rpt_item_s*                       item_ptr,
  uint32_t*                                num_pairs_ptr,
  sns_smgr_reason_pair_s_v01               reason_pairs[]);

extern sns_rh_rpt_spec_s* sns_rh_sol_find_report(
  const sns_rh_mr_header_s*  hdr_ptr,
  uint8_t                    report_id);

extern uint8_t sns_rh_sol_find_and_delete_report(
  const void* conn_handle,
  uint8_t     report_id,
  bool        flush);

extern uint32_t sns_rh_flush_reports(void);

extern void sns_rh_sol_delete_report(
  sns_rh_rpt_spec_s*      rpt_spec_ptr);

extern sns_err_code_e sns_rh_sol_process_periodic_request(
  sns_rh_mr_req_q_item_s* msg_ptr);

extern sns_err_code_e sns_rh_sol_process_buffering_request(
  sns_rh_mr_req_q_item_s* msg_ptr);

extern sns_err_code_e sns_rh_sol_process_event_gated_buffering_request(
  sns_rh_mr_req_q_item_s* msg_ptr);

extern sns_err_code_e sns_rh_sol_process_buffering_query_request(
  sns_rh_mr_req_q_item_s* msg_ptr);

extern bool sns_rh_sol_schedule_report(
  const sns_rh_mr_header_s* hdr_ptr,
  sns_rh_rpt_spec_s*        report_ptr);

extern void sns_rh_sol_deactivate_report(
  sns_rh_rpt_spec_s*      rpt_spec_ptr);

extern void sns_rh_update_periodic_like_flag(
  sns_rh_rpt_spec_s*      rpt_ptr);

extern void sns_rh_select_item_depot(
  sns_rh_rpt_item_s* item_ptr);

extern void sns_rh_sol_update_items_info(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr,
  bool                    new_items_only);

extern void sns_rh_sol_update_sensor_status(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr);

extern void sns_rh_sol_reschedule_reports(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr);

extern void sns_rh_sol_handle_pending_rpt(
  sns_rh_rpt_spec_s* rpt_ptr);

#endif /* SNS_RH_SOL_H */

