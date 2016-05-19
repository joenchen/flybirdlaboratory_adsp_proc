#ifndef SNS_SAM_IND_H
#define SNS_SAM_IND_H

/*============================================================================
  @file sns_sam_ind.h

  @brief
  All indication processing (both incoming and outgoing) for the SAM
  Framework.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include "qmi_idl_lib.h"
#include "fixed_point.h"
#include "sns_queue.h"
#include "sns_sam.h"

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
 * Handle the timer firing event for a particular client batch request.  Will
 * involve generating and sending a batch report indication, and the
 * maintanence of all output data queues.
 *
 * @param[i] clientReq The client which demands a new report to be sent
 */
void sns_sam_handle_batch( sam_client_req *clientReq );

/**
 * Send out batched indication. Will involve generating and sending a batch
 * report indication, and the maintanence of all output data queues.
 *
 * @param[i] clientReq The client which demands a new report to be sent
 */
void sns_sam_handle_batch_send_ind( sam_client_req *clientReq );

/**
 * Initialize all static objects contained within sns_sam_ind.c.
 *
 * @return SAM_ENONE
 *         SAM_ENOMEM Not enough memory to initialize Framework
 *         SAM_EFAILED Framework initialization failed
 */
sns_sam_err
sns_sam_ind_init_fw( void );

/**
 * Handle an indication message from any source.  Send the data to all
 * algorithms that have made a request to this service.
 *
 * @param[i] indMsg Indication message to process
 *
 * @note Message buffer will be freed by caller
 */
void
sns_sam_handle_ind( sns_sam_ind *indMsg );

/**
 * Process the output data generated by an algorithm instance.  Send report
 * indications as necessary, and maintain all output data queues (algorithm
 * instance and Client Request).
 *
 * @param[i] algoInst Algorithm instance which generated the data
 * @param[i] outputData Output of the recent run of the algorithm
 *
 * @return SAM_ENONE
 *         SAM_ENOMEM Not enough memory to send indication message
 *         SAM_ESTATE Unable to cancel one-shot sensor
 */
sns_sam_err
sns_sam_process_output( sns_sam_algo_inst *algoInst,
  sns_sam_algo_output *outputData );

/**
 * Handle all expired report timers.
 */
void
sns_sam_handle_report_timer( void );

/**
 * Handle all expired batch timers.
 */
void
sns_sam_handle_batch_timer( void );

/**
 * Handle all expired duty cycle timers.
 */
void
sns_sam_handle_dc_timer( void );

/**
 * Timer callback for duty cycle events.
 *
 * @param[i] algoInst The instance whose duty cycle state to change
 */
void
sns_sam_timer_cb_dc( sns_sam_algo_inst *algoInst );

/**
 * Timer callback for report or batch generation events.
 *
 * @param[i] clientReq Client to generate a request for
 */
void
sns_sam_client_timer_cb( sam_client_req *clientReq );

/**
 * Handle the timer firing event for a particular client request report.  Will
 * involve generating and sending a report indication (if non batching client),
 * and the maintanence of all output data queues.
 *
 * @param[i] clientReq The client which demands a new report to be generated
 */
void sns_sam_handle_report( sam_client_req *clientReq );

/**
 * Remove the oldest and unused output data from an algorithm instance. Search
 * through all associated client requests, and check if any of them are still
 * using this data.
 *
 * @param[i] algoInst Algorithm instance to prune
 *
 * @return PENDING
 */
void sns_sam_prune_output_head( sns_sam_algo_inst *algoInst );

#endif /* SNS_SAM_IND_H */
