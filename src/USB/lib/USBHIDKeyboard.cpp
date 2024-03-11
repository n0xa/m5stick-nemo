/*
  Keyboard.cpp

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "USBHID.h"
#if SOC_USB_OTG_SUPPORTED

#if CONFIG_TINYUSB_HID_ENABLED
#include "layouts.h"
#include "USBHIDKeyboard.h"
#include <Arduino.h>

ESP_EVENT_DEFINE_BASE(ARDUINO_USB_HID_KEYBOARD_EVENTS);
esp_err_t arduino_usb_event_post(esp_event_base_t event_base, int32_t event_id, void *event_data, size_t event_data_size, TickType_t ticks_to_wait);
esp_err_t arduino_usb_event_handler_register_with(esp_event_base_t event_base, int32_t event_id, esp_event_handler_t event_handler, void *event_handler_arg);

void USBHIDKeyboard::begin(int layout_switch){ // edit this to add layouts!
    switch (layout_switch) {
        case 1:
            memcpy(&asciimap, &de_asciimap, sizeof(de_asciimap));
            break;
        case 2:
            memcpy(&asciimap, &uk_asciimap, sizeof(uk_asciimap));
            break;
        case 3:
            memcpy(&asciimap, &es_asciimap, sizeof(es_asciimap));
            break;
        case 4:
            memcpy(&asciimap, &fr_asciimap, sizeof(fr_asciimap));
            break;
        case 6:
            memcpy(&asciimap, &it_asciimap, sizeof(it_asciimap));
            break;
        case 7:
            memcpy(&asciimap, &pt_br_asciimap, sizeof(pt_br_asciimap));
            break;
        default:
            memcpy(&asciimap, &us_asciimap, sizeof(us_asciimap));
    }
    hid.begin();
}

static const uint8_t report_descriptor[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(HID_REPORT_ID_KEYBOARD))
};

USBHIDKeyboard::USBHIDKeyboard(): hid(HID_ITF_PROTOCOL_KEYBOARD), shiftKeyReports(true){
    static bool initialized = false;
    if(!initialized){
        initialized = true;
        memset(&_keyReport, 0, sizeof(KeyReport));
        hid.addDevice(this, sizeof(report_descriptor));
    }
}

uint16_t USBHIDKeyboard::_onGetDescriptor(uint8_t* dst){
    memcpy(dst, report_descriptor, sizeof(report_descriptor));
    return sizeof(report_descriptor);
}

void USBHIDKeyboard::end(){
}

void USBHIDKeyboard::onEvent(esp_event_handler_t callback){
    onEvent(ARDUINO_USB_HID_KEYBOARD_ANY_EVENT, callback);
}
void USBHIDKeyboard::onEvent(arduino_usb_hid_keyboard_event_t event, esp_event_handler_t callback){
    arduino_usb_event_handler_register_with(ARDUINO_USB_HID_KEYBOARD_EVENTS, event, callback, this);
}

void USBHIDKeyboard::_onOutput(uint8_t report_id, const uint8_t* buffer, uint16_t len){
    if(report_id == HID_REPORT_ID_KEYBOARD){
        arduino_usb_hid_keyboard_event_data_t p;
        p.leds = buffer[0];
        arduino_usb_event_post(ARDUINO_USB_HID_KEYBOARD_EVENTS, ARDUINO_USB_HID_KEYBOARD_LED_EVENT, &p, sizeof(arduino_usb_hid_keyboard_event_data_t), portMAX_DELAY);
    }
}

void USBHIDKeyboard::sendReport(KeyReport* keys)
{
    hid_keyboard_report_t report;
    report.reserved = 0;
    report.modifier = keys->modifiers;
    memcpy(report.keycode, keys->keys, 6);
    hid.SendReport(HID_REPORT_ID_KEYBOARD, &report, sizeof(report));
}

void USBHIDKeyboard::setShiftKeyReports(bool set)
{
    shiftKeyReports = set;
}

size_t USBHIDKeyboard::pressRaw(uint16_t k) 
{
    uint16_t i;
    if (k >= 0xE0 && k < 0xE8) {
        // it's a modifier key
        _keyReport.modifiers |= (1<<(k-0x80));
    } else if (k && k < 0xA5) {
        // Add k to the key report only if it's not already present
        // and if there is an empty slot.
        if (_keyReport.keys[0] != k && _keyReport.keys[1] != k && 
            _keyReport.keys[2] != k && _keyReport.keys[3] != k &&
            _keyReport.keys[4] != k && _keyReport.keys[5] != k) {
            
            for (i=0; i<6; i++) {
                if (_keyReport.keys[i] == 0x00) {
                    _keyReport.keys[i] = k;
                    break;
                }
            }
            if (i == 6) {
                return 0;
            }   
        }
    } else {
        //not a modifier and not a key
        return 0;
    }
    sendReport(&_keyReport);
    return 1;
}

size_t USBHIDKeyboard::releaseRaw(uint16_t k) 
{
    uint8_t i;
    if (k >= 0xE0 && k < 0xE8) {
        // it's a modifier key
        _keyReport.modifiers &= ~(1<<(k-0x80));
    } else if (k && k < 0xA5) {
        // Test the key report to see if k is present.  Clear it if it exists.
        // Check all positions in case the key is present more than once (which it shouldn't be)
        for (i=0; i<6; i++) {
            if (0 != k && _keyReport.keys[i] == k) {
                _keyReport.keys[i] = 0x00;
            }
        }
    } else {
        //not a modifier and not a key
        return 0;
    }

    sendReport(&_keyReport);
    return 1;
}

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t USBHIDKeyboard::press(uint8_t k) 
{
    if (k >= 0x88) {         // it's a non-printing key (not a modifier)
        k = k - 0x88;
    } else if (k >= 0x80) {  // it's a modifier key
        _keyReport.modifiers |= (1<<(k-0x80));
        k = 0;
    } else {                // it's a printing key
        k = _asciimap[k];
        if (!k) {
            return 0;
        }
        if (k & 0x80) {                     // it's a capital letter or other character reached with shift
            // At boot, some PCs need a separate report with the shift key down like a real keyboard.
            if (shiftKeyReports) {
                pressRaw(HID_KEY_SHIFT_LEFT);
            } else {
                _keyReport.modifiers |= 0x02;   // the left shift modifier
            }
            k &= 0x7F;
        }
    }
    return pressRaw(k);
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t USBHIDKeyboard::release(uint8_t k) 
{
    if (k >= 0x88) {         // it's a non-printing key (not a modifier)
        k = k - 0x88;
    } else if (k >= 0x80) {  // it's a modifier key
        _keyReport.modifiers &= ~(1<<(k-0x80));
        k = 0;
    } else {                // it's a printing key
        k = _asciimap[k];
        if (!k) {
            return 0;
        }
        if (k & 0x80) {                         // it's a capital letter or other character reached with shift
            if (shiftKeyReports) {
                releaseRaw(k & 0x7F);           // Release key without shift modifier
                k = HID_KEY_SHIFT_LEFT;         // Below, release shift modifier
            } else {
                _keyReport.modifiers &= ~(0x02);    // the left shift modifier
                k &= 0x7F;
            }
        }
    }
    return releaseRaw(k);
}

void USBHIDKeyboard::releaseAll(void)
{
    _keyReport.keys[0] = 0;
    _keyReport.keys[1] = 0; 
    _keyReport.keys[2] = 0;
    _keyReport.keys[3] = 0; 
    _keyReport.keys[4] = 0;
    _keyReport.keys[5] = 0; 
    _keyReport.modifiers = 0;
    sendReport(&_keyReport);
}

size_t USBHIDKeyboard::write(uint8_t c)
{
    uint8_t p = press(c);  // Keydown
    release(c);            // Keyup
    return p;              // just return the result of press() since release() almost always returns 1
}

size_t USBHIDKeyboard::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        if (*buffer != '\r') {
            if (write(*buffer)) {
              n++;
            } else {
              break;
            }
        }
        buffer++;
    }
    return n;
}

void USBHIDKeyboard::writeWLayout(const char * str)
{
    int len = strlen(str);
    int  asciimap_size = sizeof(asciimap) / sizeof (ALT_GR_CHARS);
    for ( int i = 0; i < len; i++ ) {
        for ( int j = 0; j < asciimap_size ; j++ ) {
            if  (asciimap[j].c == str[i])  {
                int ksize = sizeof(asciimap[j].k) / sizeof (char);
                for ( int k = 0; k < ksize; k++ ) {
                    pressRaw(asciimap[j].k[k]);
                }
                releaseAll();
                break;
            }
        }
    }
}

#endif /* CONFIG_TINYUSB_HID_ENABLED */
#endif /* SOC_USB_OTG_SUPPORTED */
