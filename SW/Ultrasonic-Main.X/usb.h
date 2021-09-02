//Functions used for the USB communication

#ifndef MY_USB_H
#define	MY_USB_H

#include <xc.h>
#include "mcc_generated_files/usb/usb.h"

#define USB_EEPROM_READ_REQUEST 0x7A

struct USB_BUFFERS {
    uint8_t read[64];
    uint8_t write[64];
};

void USB_Transfer(struct USB_BUFFERS* usb_buffers);

#endif	/* MY_USB_H */

