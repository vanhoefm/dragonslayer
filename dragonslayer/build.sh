#!/bin/bash
set -e

# Build hostapd
cd ../hostapd/
cp defconfig .config
make clean
make -j 2

# Build wpa_supplicant
cd ../wpa_supplicant/
cp defconfig .config
make clean
make -j 2
cd ../dragonslayer/

