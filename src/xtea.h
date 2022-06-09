#ifndef __XTEA_H
#define __XTEA_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

char *xtea_encrypt(uint8_t *data, uint8_t const *key);
char *xtea_decrypt(uint8_t *data, uint8_t const *key, uint32_t len);

#endif
