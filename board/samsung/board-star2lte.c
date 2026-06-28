/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022, Markuss Broks <markuss.broks@gmail.com>
 * Copyright (c) 2024, Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 * Copyright (c) 2026, Ihor Harayda <garaigor245@gmail.com>
 */
#include <board.h>
#include <util.h>
#include <drivers/framework.h>
#include <lib/simplefb.h>

#define DECON_F_BASE		0x16030000
#define HW_SW_TRIG_CONTROL	0x70

// Early initialization
int star2lte_init(void)
{
	/* Allow framebuffer to be written to */
	*(int*) (DECON_F_BASE + HW_SW_TRIG_CONTROL) = 0x1281;
	return 0;
}

static struct video_info star2lte_fb = {
	.format = FB_FORMAT_ARGB8888,
	.width = 2960,
	.height = 1440,
	.stride = 4,
	.address = (void *)0xcc000000
};

static const struct device star2lte_devices[] = {
	{ "simplefb", &star2lte_fb, "fb" },
};

struct board_data board_ops = {
	.name = "samsung-star2lte",
	.ops = {
		.early_init = star2lte_init,
	},
	.devices = star2lte_devices,
	.num_devices = ARRAY_SIZE(star2lte_devices),
	.quirks = 0
};

