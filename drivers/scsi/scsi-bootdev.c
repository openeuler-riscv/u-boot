// SPDX-License-Identifier: GPL-2.0+
/*
 * Bootdevice for NVMe
 *
 * Copyright 2025 ISCAS
 * Polluted by Hangfan Li <lihangfan@iscas.ac.cn>
 */

#include <common.h>
#include <bootdev.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <scsi.h>

static int scsi_get_blk(struct udevice *dev, struct udevice **blkp)
{
	struct udevice *blk;
	int ret;

	device_find_first_child_by_uclass(dev, UCLASS_BLK, &blk);
	ret = device_probe(blk);
	if (ret)
		return ret;
	*blkp = blk;

	return 0;
}

static int scsi_get_bootflow(struct udevice *dev, struct bootflow_iter *iter,
			    struct bootflow *bflow)
{
	struct udevice *scsi_dev = dev_get_parent(dev);
	struct udevice *blk;
	int ret;

	ret = scsi_get_blk(scsi_dev, &blk);
	/*
	 * If there is no media, indicate that no more partitions should be
	 * checked
	 */
	if (ret == -EOPNOTSUPP)
		ret = -ESHUTDOWN;
	if (ret)
		return log_msg_ret("blk", ret);
	assert(blk);
	ret = bootdev_find_in_blk(dev, blk, iter, bflow);
	if (ret)
		return log_msg_ret("find", ret);

	return 0;
}

static int scsi_bootdev_bind(struct udevice *dev)
{
	struct bootdev_uc_plat *ucp = dev_get_uclass_plat(dev);

	ucp->prio = BOOTDEVP_3_SCAN_SLOW;

	return 0;
}

static int scsi_bootdev_probe(struct udevice *dev)
{
	scsi_scan(false);
	return 0;
}

struct bootdev_ops scsi_bootdev_ops = {
	.get_bootflow	= scsi_get_bootflow,
};

static const struct udevice_id scsi_bootdev_ids[] = {
	{ .compatible = "u-boot,bootdev-scsi" },
	{ }
};

U_BOOT_DRIVER(scsi_bootdev) = {
	.name		= "scsi_bootdev",
	.id		= UCLASS_BOOTDEV,
	.ops		= &scsi_bootdev_ops,
	.bind		= scsi_bootdev_bind,
	.probe		= scsi_bootdev_probe,
	.of_match	= scsi_bootdev_ids,
};
