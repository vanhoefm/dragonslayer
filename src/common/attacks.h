/*
 * dragon-slayer
 * Copyright (c) 2019, Mathy Vanhoef <Mathy.Vanhoef@nyu.edu>
 *
 * This code may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#ifndef ATTACKS_H_
#define ATTACKS_H_

// This is always defined and used to track the changes we
// made to the original hostap code.
#define DRAGONSLAYER

extern int dragonslayer_reflect;
extern int dragonslayer_invalidcurve;
extern int dragonslayer_invalidcurve_aruba;
extern int dragonslayer_badscalar;

void poc_log(const u8 *clientmac, const char *format, ...);

#endif // ATTACKS_H_
