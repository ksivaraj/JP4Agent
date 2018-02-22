#!/bin/bash
#
# VMX setup scripts
#
# Created by Sandesh Kumar Sodhi, December 2017
# Copyright (c) [2017] Juniper Networks, Inc. All rights reserved.
#
# All rights reserved.
#
# Notice and Disclaimer: This code is licensed to you under the Apache
# License 2.0 (the "License"). You may not use this code except in compliance
# with the License. This code is not an official Juniper product. You can
# obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Third-Party Code: This code may depend on other components under separate
# copyright notice and license terms. Your use of the source code for those
# components is subject to the terms and conditions of the respective license
# as noted in the Third-Party source code file.
#

JP4AGENT_DIR=/root/JP4Agent
SCRIPTS_DIR=$JP4AGENT_DIR/tools/docker/scripts  
CFG_FILES_DIR=$JP4AGENT_DIR/tools/docker/cfg
VMX_IMAGES_LOC=/root/VMX
VMX_DIR=$VMX_IMAGES_LOC/vmx
NEW_SCRIPTS_DIR=$VMX_IMAGES_LOC/vmx/config
VMX_CONFIG_FILE=$JP4AGENT_DIR/tools/config/vmx-cfg.xml

CP=/bin/cp
PS=/bin/ps
TAR=/bin/tar
DATE=/bin/date
MOUNT=/bin/mount
APPARMOR_PARSER=/sbin/apparmor_parser
CHOWN=/bin/chown
SED=/bin/sed
BRCTL=/sbin/brctl
VIRSH=/usr/bin/virsh
ETHTOOL=/sbin/ethtool
GREP=/bin/grep
CRON=/usr/sbin/cron
CRONTAB=/usr/bin/crontab

me=`basename "$0"`
#
# Run a bash shell command
#
function run_command {
    DATE_STR=`$DATE`
    echo "[$DATE_STR] [$me] Executing command \"$@\" ..."
    $@  
    if [ $? -eq 0 ] 
    then
      DATE_STR=`$DATE`
      echo "[$DATE_STR] [$me] Command \"$@ \" : SUCCESS"
    else
      DATE_STR=`$DATE`
      echo "[$DATE_STR] [$me] Command \"$@ \": ERROR"
      exit 1
    fi  
}

#
# Display a log message which stands out
#
function log_prominent {
    DATE_STR=`$DATE`
    echo ""
    echo ""
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "$DATE_STR [$me]"
    echo $@ 
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo ""
    echo ""
}  

#
# Error log
#
function log_error {
    DATE_STR=`$DATE`
    echo ""
    echo "~~~~~~~~ ERROR ~~~~~~~~~~~~~~~"
    echo "~~~~~~~~ ERROR ~~~~~~~~~~~~~~~"
    echo "[$DATE_STR] [$me] ERROR: $@" 
    echo "~~~~~~~~ ERROR ~~~~~~~~~~~~~~~"
    echo "~~~~~~~~ ERROR ~~~~~~~~~~~~~~~"
    echo ""
}  

#
# Debug log
#
function log_debug {
    DATE_STR=`$DATE`
    echo ""
    echo "~~~~~~~~ DEBUG ~~~~~~~~~~~~~~~"
    echo "[$DATE_STR] [$me] DEBUG: $@" 
    echo "~~~~~~~~ DEBUG ~~~~~~~~~~~~~~~"
    echo ""
}  
