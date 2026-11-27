#ifndef PDU_H
#define PDU_H
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#define ENTIY_STATE_LENGTH 42
struct PduHeader 
{
    uint8_t ver;
    uint8_t type;
    uint16_t length;

};

struct EntityState
{
    struct PduHeader header;
    uint16_t ID;
    double x, y, z;
    float vx, vy, vz;
};

size_t serialize (const struct EntityState *e, uint8_t *buf)
{
    //struct has 1 + 1 + 2 + 2 +(8*3) + (4*3) = 42 btyes. uint8_t takes only 8 bits (1 byte)
    size_t pos = 0;
    //Ver and type
    buf[pos++] = e-> header.ver;
    buf [pos++] = e-> header.type;
    //Length
    buf [pos++] = (uint8_t)(ENTIY_STATE_LENGTH>>8);
    buf [pos++] = (uint8_t)(ENTIY_STATE_LENGTH);
    //ID
    buf [pos++] = (uint8_t)(e->ID>>8);
    buf [pos++] = (uint8_t) (e->ID);
    //double pos
    uint64_t bits;
    memcpy(&bits,&e->x,sizeof(bits));
    for (int s =56; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(bits>>s);}
    memcpy(&bits,&e->y,sizeof(bits));
    for (int s =56; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(bits>>s);}
    memcpy(&bits,&e->z,sizeof(bits));
    for (int s =56; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(bits>>s);}
    
    //float velocity
    uint32_t btyes;
    memcpy(&btyes,&e->vx,sizeof(btyes));
    for (int s =24; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(btyes>>s);}
    memcpy(&btyes,&e->vy,sizeof(btyes));
    for (int s =24; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(btyes>>s);}
    memcpy(&btyes,&e->vz,sizeof(btyes));
    for (int s =24; s>=0; s-=8)
    {buf[pos++] = (uint8_t)(btyes>>s);}
  
    return pos;
}

#endif