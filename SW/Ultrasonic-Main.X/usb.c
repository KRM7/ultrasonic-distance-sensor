#include "usb.h"
#include "xc.h"
#include "mcc_generated_files/usb/usb.h"
#include "eeprom.h"


void USB_Transfer(struct USB_BUFFERS* usb_buffers)
{
    if (USBGetDeviceState() < CONFIGURED_STATE) return;
    if (USBIsDeviceSuspended() == true) return;
    
    if (USBUSARTIsTxTrfReady() == true)
    {
        bool read_request = false;

        //USB read
        uint8_t num_bytes_read = getsUSBUSART(usb_buffers->read, sizeof(usb_buffers->read));

        uint8_t i;
        for(i = 0; i < num_bytes_read; i++)
        {
            if (usb_buffers->read[i] == USB_EEPROM_READ_REQUEST)
            {
                read_request = true;
            }
        }

        //USB write
        if (num_bytes_read > 0 && read_request)
        {          
            uint16_t i;
            for (i = 0; i < 512; i++)
            {
                uint8_t page[64];
                EEPROM_PageRead(i, &page[0]);
                
                //send page
                uint16_t j;
                for(j = 0; j < 64; j++)
                {
                    usb_buffers->write[j] = page[j];
                }
                
                putUSBUSART(usb_buffers->write, sizeof(usb_buffers->write));
                CDCTxService();
            }       
        }
    }
}