// SPDX-License-Identifier: GPL-2.0
/* Author: Dan Scally <djrscally@gmail.com> */
#ifndef __CIO2_BRIDGE_H
#define __CIO2_BRIDGE_H

#include <linux/property.h>

#define CIO2_HID				"INT343E"
#define CIO2_PCI_ID				0x9d32

#define NODE_SENSOR(_HID, _PROPS)		\
	((const struct software_node) {		\
		.name = _HID,			\
		.properties = _PROPS,		\
	})

#define NODE_PORT(_PORT, _SENSOR_NODE)		\
	((const struct software_node) {		\
		_PORT,				\
		_SENSOR_NODE,			\
	})

#define NODE_ENDPOINT(_EP, _PORT, _PROPS)	\
	((const struct software_node) {		\
		_EP,				\
		_PORT,				\
		_PROPS,				\
	})

enum cio2_sensor_swnodes {
        SWNODE_SENSOR_HID,
        SWNODE_SENSOR_PORT,
        SWNODE_SENSOR_ENDPOINT,
        SWNODE_CIO2_PORT,
        SWNODE_CIO2_ENDPOINT,
        NR_OF_SENSOR_SWNODES
};

/* Data representation as it is in ACPI SSDB buffer */
struct cio2_sensor_ssdb {
	u8 version;
	u8 sku;
	u8 guid_csi2[16];
	u8 devfunction;
	u8 bus;
	u32 dphylinkenfuses;
	u32 clockdiv;
	u8 link;
	u8 lanes;
	u32 csiparams[10];
	u32 maxlanespeed;
	u8 sensorcalibfileidx;
	u8 sensorcalibfileidxInMBZ[3];
	u8 romtype;
	u8 vcmtype;
	u8 platforminfo;
	u8 platformsubinfo;
	u8 flash;
	u8 privacyled;
	u8 degree;
	u8 mipilinkdefined;
	u32 mclkspeed;
	u8 controllogicid;
	u8 reserved1[3];
	u8 mclkport;
	u8 reserved2[13];
} __packed__;

struct cio2_sensor {
	char name[ACPI_ID_LEN];
	struct acpi_device *adev;
	struct software_node swnodes[6];
	struct property_entry ep_properties[4];
	struct property_entry dev_properties[3];
	struct property_entry cio2_properties[3];
        struct software_node_ref_args local_ref[1];
        struct software_node_ref_args remote_ref[1];
	struct cio2_sensor_ssdb ssdb;
};

struct cio2_bridge {
	struct device *cio2_dev;
	unsigned int n_sensors;
	struct cio2_sensor sensors[CIO2_NUM_PORTS];
};

#endif
