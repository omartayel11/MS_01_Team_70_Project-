#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"slot1", "slot2", "slot3", "slot4"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
    size_t printed;
    switch (iIndex) {
    case 0: { 
        bool slot1_status = !gpio_get(12);
        printed = snprintf(pcInsert, iInsertLen, slot1_status ? "Occupied" : "Free");
        break;
    }
    case 1: { 
        bool slot1_status = !gpio_get(13);
        printed = snprintf(pcInsert, iInsertLen, slot1_status ? "Occupied" : "Free");
        break;
    }
    case 2: { 
        bool slot1_status = !gpio_get(14);
        printed = snprintf(pcInsert, iInsertLen, slot1_status ? "Occupied" : "Free");
        break;
    }
    case 3: { 
        bool slot1_status = !gpio_get(15);
        printed = snprintf(pcInsert, iInsertLen, slot1_status ? "Occupied" : "Free");
        break;
    }
    default:
        printed = 0;
        break;
    }
    return (u16_t)printed;
}

void ssi_init() {
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
