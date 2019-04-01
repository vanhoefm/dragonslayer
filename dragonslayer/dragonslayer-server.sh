#!/bin/bash
HOSTAPD=./../hostapd/hostapd

if [ ! -f $HOSTAPD ]; then
	echo "File $HOSTAPD not found. Did you build hostapd?"
	exit 1
fi

$HOSTAPD hostapd.conf $@
