// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017 NXP Semiconductors
 * Copyright (C) 2017 Bin Meng <bmeng.cn@gmail.com>
 */

#define LOG_CATEGORY UCLASS_NVME

#include <common.h>
#include <dm.h>
#include <bootdev.h>

static int nvme_post_bind(struct udevice *dev)
{
	int ret;

	ret = bootdev_setup_for_dev(dev, "nvme_bootdev");
	if (ret)
		return log_msg_ret("bootdev", ret);

	return 0;
}

UCLASS_DRIVER(nvme) = {
	.name	= "nvme",
	.id	= UCLASS_NVME,
	.post_bind	= nvme_post_bind,
};
