#!/bin/bash
SUPPLICANT=./../wpa_supplicant/wpa_supplicant

# Check that wpa_supplicant was compiled
if [ ! -f $SUPPLICANT ]; then
	echo "File $SUPPLICANT not found. Did you build wpa_supplicant?"
	exit 1
fi

$SUPPLICANT -D nl80211 -c client.conf $@
