// SPDX-License-Identifier: GPL-2.0
/*
 * ESWIN uboot-2024
 *
 * Copyright 2024, Beijing ESWIN Computing Technology Co., Ltd.. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Xiang Xu <xuxiang@eswincomputing.com>
 */
#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#define CFG_EXTRA_ENV_SETTINGS \
    "fdt_high=0xffffffffffffffff\0" \
    "initrd_high=0xffffffffffffffff\0" \
    "kernel_addr_r=0x84000000\0" \
    "fdt_addr_r=0x88000000\0" \
    "fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
    "scriptaddr=0x88100000\0" \
    "pxefile_addr_r=0x88200000\0" \
    "ramdisk_addr_r=0x88300000\0" \
    "stdin=serial,usbkbd\0" \
    "stderr=vidconsole,serial\0" \
    "stdout=serial\0" \
    "kernel_comp_addr_r=0x98300000\0" \
    "kernel_comp_size=0x10000000\0" \
    "splashimage=0xe0000000\0" \
    "splashpos=0,0\0"

#endif /* __CONFIG_H */
