#===============================================================================
#
# CBSP Buils system
#
# General Description
#    build rename log file.
#
# Copyright (c) 2009-2009 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
# $Header: //components/rel/scons.qc/1.1/build/rename-log.sh#2 $
# $DateTime: 2014/09/17 11:57:18 $
# $Author: pwbldsvc $
# $Change: 6612467 $
#                      EDIT HISTORY FOR FILE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
#
#===============================================================================

log_file_name="build-log"
log_file_ext=".txt"
log_file="$log_file_name$log_file_ext"

if [ -f $log_file ]; then
   for i in {001..1000}; do
      i=`printf '%.03d' $i`
      old_log_file="$log_file_name-$i$log_file_ext"
      
      if [ ! -f $old_log_file ]; then
         break
      fi
   done

   if [ $i != "1000" ]; then
      mv $log_file $old_log_file
   fi
fi 

