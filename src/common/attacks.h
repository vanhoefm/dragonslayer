/*
 * krackattacks
 * Copyright (c) 2019, Mathy Vanhoef <Mathy.Vanhoef@nyu.edu>
 *
 * This code may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#ifndef ATTACKS_H_
#define ATTACKS_H_

// This is always defined. Use to clearly mark the changes we
// made to the original hostap code.
#define DRAGONBLOOD

// Make changes to hostapd and wpa_supplicant to test several
// of the DragonBlood attacks.
//#define DRAGONBLOOD_INVALID_CUVE

// Invalid curve attack against Aruba's Windows client: use a
// scalar equal to zero, and as element the point at infinity.
// Only has an effect if DRAGONBLOOD_INVALID_CUVE is also set.
#define DRAGONBLOOD_ARUBA_CLIENT

// Perform reflection attacks against both SAE clients and against
// EAP-PWD server implementations.
#define DRAGONBLOOD_REFLECT

void poc_log(const u8 *clientmac, const char *format, ...);

#endif // ATTACKS_H_
