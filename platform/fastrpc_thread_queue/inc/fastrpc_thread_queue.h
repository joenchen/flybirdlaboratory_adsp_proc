/*========================================================================

  Copyright (c) 2012 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.
  ====================================================================== */
#ifndef FASTRPC_THREAD_QUEUE_H
#define FASTRPC_THREAD_QUEUE_H

#include "AEEQList.h"
#include "AEEStdDef.h"
#include "AEEQListExt.h"
#include "fastrpc_internal.h"
#include "fastrpc_port.h"
#include "AEEatomic.h"
#include "HAP_farf.h"
#include "qurt_thread.h"
#include "qurt_mutex.h"

/**
 * library for keeping track of threads and PDs to service HLOS FastRPC requests
 * should never allocate when enqueueing
 */

struct ftq_thread;
/**
 * reserved messages used to avoid allocation when a thread isn't there yet
 */
struct ftq_rmsg {
   QNode qn;
   struct fastrpc_port_msg msg;
};

/**
 * a threads space for a messge, could be usermalloced, so we cant trust the contents
 */
struct ftq_umsg {
   uint32 fut;
   uint32 valid;
   struct fastrpc_port_msg msg;
};

struct ftq_group;
/**
 * a thread struture, could be in the kernel or user pd
 */
struct ftq_thread {
   QNode AA; //! key for looking up by android thread id
   QNode QQ; //! key for looking up by qurt thread id
   QNode GC; //! key for looking up by qurt thread id
   struct ftq_umsg *umsg;  //! space for messages, could be usermalloced
   struct ftq_group *pgrp;
   qurt_thread_t tidQ;     
   int tidA;
   boolean isMigrated;
};

struct ftq_groups;

DEFINE_TQLIST(group_threads, struct ftq_thread, QQ);
DEFINE_TQLIST(gc_threads, struct ftq_thread, GC);
DEFINE_TQLIST(pending_invokes, struct ftq_rmsg, qn);
DEFINE_TQLIST(new_invokes, struct ftq_rmsg, qn);
//! group of threads in the kernel or for a pd, representing a single HLOS pd
struct ftq_group {
   group_threads threadsQ;
   gc_threads threadsGC;
   struct ftq_thread* thread0;  //! the main thread used for creating new threads
   struct ftq_groups* procs;
   QNode AA;                    //! key for HLOS pid
   int client_handle;
   int asid;
   int pidA;
   char name[256];
   /** 
    * invokes and pending are lists of ftq_rmsg
    * anything in these lists should come from procs->free
    */
   new_invokes invokes;  //! new incomming messages for thread0
   pending_invokes pending;  //! pending messages for newly created threads
};

static __inline int ftq_umsg_is_valid(struct ftq_umsg* me) {
   return atomic_CompareAndExchange(&me->valid, 1, 1) == 1;
}

static __inline void ftq_umsg_invalidate(struct ftq_umsg* me) {
   atomic_Exchange(&me->valid, 0);
}

static __inline void ftq_umsg_exit(struct ftq_umsg* me) {
   atomic_Exchange(&me->fut, 2);
   FARF(LOW, "ftq msg exit 2 %p", &me->fut);
   qurt_futex_wake(&me->fut, 2);
}

static __inline int ftq_umsg_has_exited(struct ftq_umsg* me) {
   return (2 == atomic_CompareAndExchange(&me->fut, 2, 2));
}

static __inline int ftq_umsg_wake(struct ftq_umsg* me) {
   uint32 prev = atomic_CompareAndExchange(&me->fut, 1, 0);
   if(prev == 0) {
      FARF(LOW, "ftq msg wake 1 %p", &me->fut);
      qurt_futex_wake(&me->fut, 1);
   }
   return ftq_umsg_has_exited(me);
}


static __inline int ftq_umsg_wait(struct ftq_umsg* me) {
   while(0 == atomic_CompareAndExchange(&me->fut, 0, 0)) {
      FARF(LOW, "ftq msg wait %p %d", &me->fut, me->fut);
      qurt_futex_wait(&me->fut, 0);
      FARF(LOW, "ftq msg woke %p %d", &me->fut, me->fut);
   }
   atomic_CompareAndExchange((uint32*)&me->fut, 0, 1);
   return ftq_umsg_has_exited(me);
}

void ftq_deinit(void(*group_dtor)(int pidA));

struct ftq_thread* ftq_thread_find(qurt_thread_t tidQ);
struct ftq_group* ftq_group_lookup(int client_handle);
int ftq_group_pidA_to_asid(int pidA, int* asid);

int ftq_enqueue(struct fastrpc_port_msg* msg);

int ftq_group_init(int pidA, struct ftq_group* pgrp);
int ftq_group_default_init(int pidA);
int ftq_group_default_deinit(int pidA,
                     void(*thread_dtor)(struct ftq_thread* th),
                     int ret);

boolean ftq_group_is_default(int pidA);
 
struct ftq_group* ftq_group_deinit(int pidA, void(*thread_dtor)(struct ftq_thread* th),
                                   int ret);

struct ftq_thread* ftq_thread_exit(struct ftq_group* pgrp, qurt_thread_t tidQ);

void ftq_group_cleanup_threads(struct ftq_group* pgrp,
                              qurt_thread_t self,
                              void(*thread_dtor)(struct ftq_thread* th));

int ftq_group_notify(struct ftq_group* pgrp);
int ftq_thread_notify(struct ftq_group* pgrp, qurt_thread_t tidQ);

void ftq_group_exit(int pidA);

//! thread 0 should use this to respond to newly created thread requests
int ftq_thread0_requeue(struct ftq_group* pgrp, qurt_thread_t tidQ);
int ftq_thread0_requeue_pid(struct ftq_thread* th, int pidA);

int ftq_thread0_init(struct ftq_group* pgrp,
                     struct ftq_thread* th, 
                     struct ftq_umsg* umsg,
                     qurt_thread_t tidQ);
/**
 * migrate thread into the defaultPID, blocking until the PID is created
 */
int ftq_thread_migrate_default(struct ftq_thread* th, 
                               struct ftq_umsg* umsg,
                               qurt_thread_t tidQ,
                               int(*init_locked)(struct ftq_thread* th));
/**
 * if tidA is 0, then we are creating thread0
 * otherwise, a pending message must be in the pgrp->pending list with the tidA id
 */
int ftq_thread_init(struct ftq_group* pgrp,
                    struct ftq_thread* th, 
                    struct ftq_umsg* pumsg,
                    int tidA,
                    qurt_thread_t tidQ);
//! normal response
void ftq_thread_respond(struct ftq_group* pgrp, qurt_thread_t tidQ, int ret);

void ftq_group_respond_pending(struct ftq_group* pgrp, int tidA, int ret);

void ftq_thread_deinit(struct ftq_thread* th, int ret);

static __inline int ftq_is_kernel_msg(struct fastrpc_port_msg* msg) {
   return 0 == msg->msg.pid || msg->msg.invoke.header.handle == 1;
}

#endif // FASTRPC_THREAD_QUEUE_H

