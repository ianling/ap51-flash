/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Marek Lindner <mareklindner@neomailbox.ch>
 */

#ifndef __AP51_FLASH_ROUTER_TYPES_H__
#define __AP51_FLASH_ROUTER_TYPES_H__

#include <stdint.h>

#include "ap51-flash.h"

struct node;

/**
 * each router type has to declare a router_type struct
 * and add a pointer to the router_types array
 *
 * detect_pre: called by the scheduler in regular intervals
 *             can be used to send ARP requests
 * detect_main: called when an ARP packet is received
 *              return 1 if the router has been detected
 * detect_post: called to let the router_type configure
 *              the node#s settings (e.g. IP)
 */
struct router_type {
	char desc[DESC_MAX_LENGTH];
	void (*detect_pre)(const uint8_t *our_mac);
	int (*detect_main)(void *priv, const char *packet_buff,
			   int packet_buff_len);
	void (*detect_post)(struct node *node, const char *packet_buff,
			    int packet_buff_len);
	struct router_image *image;
	char *image_desc;
	int priv_size;
};

int router_types_init(void);
void router_types_detect_pre(const uint8_t *our_mac);
int router_types_detect_main(struct node *node, const char *packet_buff,
			     int packet_buff_len);

extern int router_types_priv_size;

#endif /* __AP51_FLASH_ROUTER_TYPES_H__ */
