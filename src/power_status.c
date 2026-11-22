/* Macrodeck: tell the PC app over Bluetooth whether USB power is connected
 * (PC or wall charger), so it can show "Charging".
 * Read-only characteristic, 1 byte: 1 = USB powered, 0 = on battery. */
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zmk/usb.h>

#define MD_UUID(n) BT_UUID_128_ENCODE(0x6d616372, 0x6f64, 0x6563, 0x6b00, n)

static struct bt_uuid_128 md_svc_uuid = BT_UUID_INIT_128(MD_UUID(0x000000000001));
static struct bt_uuid_128 md_pwr_uuid = BT_UUID_INIT_128(MD_UUID(0x000000000002));

static ssize_t md_read_power(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                             void *buf, uint16_t len, uint16_t offset) {
    uint8_t v = zmk_usb_is_powered() ? 1 : 0;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &v, sizeof(v));
}

BT_GATT_SERVICE_DEFINE(macrodeck_power_svc,
    BT_GATT_PRIMARY_SERVICE(&md_svc_uuid),
    BT_GATT_CHARACTERISTIC(&md_pwr_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
                           md_read_power, NULL, NULL));
