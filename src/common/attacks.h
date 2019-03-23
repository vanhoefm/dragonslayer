/*
 * krackattacks
 * Copyright (c) 2019, Mathy Vanhoef <Mathy.Vanhoef@nyu.edu>
 *
 * This code may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#ifndef ATTACKS_H_
#define ATTACKS_H_

// Make changes to hostapd and wpa_supplicant to test several
// of the DragonBlood attacks.
#define DRAGONBLOOD_TESTS

void poc_log(const u8 *clientmac, const char *format, ...);

#endif // ATTACKS_H_
