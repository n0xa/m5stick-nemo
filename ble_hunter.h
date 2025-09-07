// BLE Hunter - Bluetooth Low Energy Device Detection
// Based on ESP32Marauder's BLE sniffer implementation
// Adapted for M5Stick-NEMO

#ifndef BLE_HUNTER_H
#define BLE_HUNTER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <vector>

// BLE Hunter globals
struct BLEStats {
  uint32_t total_devices = 0;
  uint32_t unique_devices = 0;
  int32_t rssi_sum = 0;
  uint32_t rssi_count = 0;
  int32_t avg_rssi = -70;
  uint32_t last_reset_time = 0;
};

struct BLEDeviceInfo {
  String mac;
  String name;
  int32_t rssi;
  uint32_t last_seen;
  String device_type;
};

// Scan configuration
const uint32_t BLE_SCAN_TIME = 1; // Scan for 1 second intervals
const uint32_t BLE_SCAN_WINDOW = 99;
const uint32_t BLE_SCAN_INTERVAL = 100;
const uint32_t MAX_BLE_DEVICES = 50; // Limit to prevent memory overflow

// Global state
extern BLEStats ble_stats;
extern BLEScan* ble_scanner;
extern bool ble_hunter_active;
extern bool ble_channel_hop_pause;
extern std::vector<BLEDeviceInfo> seen_ble_devices;

// Function declarations
void ble_hunter_setup();
void ble_hunter_loop();
void ble_hunter_cleanup();
void start_ble_monitoring();
void stop_ble_monitoring();
void reset_ble_stats_if_needed();
void add_unique_ble_device(const String& mac, const String& name, int32_t rssi);
String detect_device_type(const String& mac, const String& name);

// BLE scan callback class
class BLEHunterCallback: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice);
};

#endif