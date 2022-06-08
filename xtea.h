#ifndef __XTEA_H
#define __XTEA_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

char *encrypt(uint8_t *data, uint8_t *key);
char *decrypt(uint8_t *data, uint8_t *key, uint32_t len);

#endif
