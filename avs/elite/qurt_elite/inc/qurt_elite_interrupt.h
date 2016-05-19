/*========================================================================
Copyright (c) 2010-2011, 2013-2014 Qualcomm Technologies, Inc. All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
========================================================================= */
/**
@file qurt_elite_interrupt.h

@brief This file contains utilities for registering with interrupts.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      qurt_elite_mainpage.dox file.
===========================================================================*/
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/inc/qurt_elite_interrupt.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/05/14   sw      (Tech Pubs) Mergeded Doxygen comments from 2.4.
03/25/13   sw      (Tech Pubs) Edited Doxygen comments/markup for 2.0.
05/03/11   leo     (Tech Pubs) Edited doxygen comments and markup.
11/04/10   psr     Created file.
========================================================================== */

#ifndef QURT_ELITE_INTERRUPT_H
#define QURT_ELITE_INTERRUPT_H

#include "qurt_elite.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


/** @addtogroup qurt_elite_interrupt
@{ */

/** Interrupt Service Thread (IST) stack size. */
#define QURT_ELITE_IST_STACK_SIZE 512

/*forward declaration*/
typedef struct qurt_elite_interrupt_ist_t qurt_elite_interrupt_ist_t;

/** Structure that contains information for registering an interrupt.

  The client must allocate the memory for this structure before calling
  qurt_elite_interrupt_register(). The client need not initialize any
  structure variables.
*/
struct qurt_elite_interrupt_ist_t
{
 char_t ist_thread_name[16];
 /**< IST thread name. */

 uint16_t intr_id;
 /**< Interrupt to register. */

 qurt_elite_thread_t thread_id;
 /**< Used to join the IST thread. */

 uint32_t ist_state;
 /**< Checks whether the IST registered the interrupt successfully. */

 void (*ist_callback)(void *);
 /**< Function pointer to the thread entry function. */

 qurt_sem_t semaphore;
 /**< Semaphore used to synchronize a caller and an IST. */

 void *arg_ptr;
 /**< Pointer to the thread arguments sent by the client. @newpagetable */
 };

/**
  Registers an interrupt. A client must allocate the memory for the
  qurt_elite_interrupt_ist_t structure.

  @datatypes
  qurt_elite_interrupt_ist_t

  @param[in] ist_ptr          Pointer to the IST.
  @param[in] intr_id          Interrupt number to register.
  @param[in] callback_ptr     Pointer to the callback function when an
                              interrupt occurs.
  @param[in] arg_ptr          Pointer to the arguments sent by the client.
  @param[in] thread_name_ptr  Pointer to the IST thread name.

  @return
  ADSPResult error code (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None. @newpage
*/ /* Q2 = Hex Multimedia: Elite API Interface Spec for 2.4 (80-NF770-13) */
ADSPResult qurt_elite_interrupt_register( qurt_elite_interrupt_ist_t *ist_ptr, uint16_t intr_id,
							  void (*callback_ptr)(void *),void *arg_ptr,char_t *thread_name_ptr);

/**
  Unregisters an interrupt.

  @datatypes
  qurt_elite_interrupt_ist_t

  @param[in] ist_ptr  Pointer to the IST.

  @return
  ADSPResult error code (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  The interrupt object must have been registered before calling this
  function.
*/
ADSPResult qurt_elite_interrupt_unregister(qurt_elite_interrupt_ist_t *ist_ptr);

/** @} */ /* end_addtogroup qurt_elite_interrupt */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef QURT_ELITE_INTERRUPT_H
