/* inc copyright */

#include "usb.h"

void usb_vcptx(const char* msg)
{
    CDC_Transmit_FS(msg, strlen(msg));
}
