#include <stdio.h>
#include <string.h>
#include "Pdu_Head.h"

int main(void) {
    struct EntityState e = {0};
    e.header.ver = 1;
    e.header.type = 1;
    e.ID = 0x0102;
    e.x = 1.0;

    uint8_t buf[64];
    size_t n = serialize(&e, buf);

    printf("wrote %zu bytes\n", n);
    for (size_t i = 0; i < n; i++)
        printf("%02X ", buf[i]);
    printf("\n");
    return 0;
}