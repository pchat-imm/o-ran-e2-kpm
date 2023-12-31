/*  =========================================================================
    ziflist - List of network interfaces available on system

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef __ZIFLIST_H_INCLUDED__
#define __ZIFLIST_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  @warning THE FOLLOWING @INTERFACE BLOCK IS AUTO-GENERATED BY ZPROJECT
//  @warning Please edit the model at "api/ziflist.api" to make changes.
//  @interface
//  This is a stable class, and may not change except for emergencies. It
//  is provided in stable builds.
//  This class has draft methods, which may change over time. They are not
//  in stable releases, by default. Use --enable-drafts to enable.
//  Get a list of network interfaces currently defined on the system
CZMQ_EXPORT ziflist_t *
    ziflist_new (void);

//  Destroy a ziflist instance
CZMQ_EXPORT void
    ziflist_destroy (ziflist_t **self_p);

//  Reload network interfaces from system
CZMQ_EXPORT void
    ziflist_reload (ziflist_t *self);

//  Return the number of network interfaces on system
CZMQ_EXPORT size_t
    ziflist_size (ziflist_t *self);

//  Get first network interface, return NULL if there are none
CZMQ_EXPORT const char *
    ziflist_first (ziflist_t *self);

//  Get next network interface, return NULL if we hit the last one
CZMQ_EXPORT const char *
    ziflist_next (ziflist_t *self);

//  Return the current interface IP address as a printable string
CZMQ_EXPORT const char *
    ziflist_address (ziflist_t *self);

//  Return the current interface broadcast address as a printable string
CZMQ_EXPORT const char *
    ziflist_broadcast (ziflist_t *self);

//  Return the current interface network mask as a printable string
CZMQ_EXPORT const char *
    ziflist_netmask (ziflist_t *self);

//  Return the list of interfaces.
CZMQ_EXPORT void
    ziflist_print (ziflist_t *self);

//  Self test of this class.
CZMQ_EXPORT void
    ziflist_test (bool verbose);

#ifdef CZMQ_BUILD_DRAFT_API
//  *** Draft method, for development use, may change without warning ***
//  Return the current interface MAC address as a printable string
CZMQ_EXPORT const char *
    ziflist_mac (ziflist_t *self);

//  *** Draft method, for development use, may change without warning ***
//  Get a list of network interfaces currently defined on the system
//  Includes IPv6 interfaces
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT ziflist_t *
    ziflist_new_ipv6 (void);

//  *** Draft method, for development use, may change without warning ***
//  Reload network interfaces from system, including IPv6
CZMQ_EXPORT void
    ziflist_reload_ipv6 (ziflist_t *self);

//  *** Draft method, for development use, may change without warning ***
//  Return true if the current interface uses IPv6
CZMQ_EXPORT bool
    ziflist_is_ipv6 (ziflist_t *self);

#endif // CZMQ_BUILD_DRAFT_API
//  @end


#ifdef __cplusplus
}
#endif

#endif
