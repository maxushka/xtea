#include "xtea.h"

static void encode(uint32_t num_rounds, uint32_t v[2], uint32_t const key[4])
{
  unsigned int i;
  uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;
  for (i = 0; i < num_rounds; i++)
  {
    v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    sum += delta;
    v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
  }
  v[0] = v0;
  v[1] = v1;
}

static void decode(uint32_t num_rounds, uint32_t v[2], uint32_t const key[4])
{
  unsigned int i;
  uint32_t v0 = v[0], v1 = v[1], delta = 0x9E3779B9, sum = delta * num_rounds;
  while (sum)
  {
    v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
    sum -= delta;
    v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
  }
  v[0] = v0;
  v[1] = v1;
}

char *xtea_encrypt(uint8_t *data, uint8_t const *key)
{
  uint32_t len = strlen(data);
  if ((len%8)>0)
  {
    len += len%8;
  }
  char *out = malloc(len);
  uint32_t enc[2] = {0};
  for (int i = 0; i < strlen(data); i+=8)
  {
    memcpy(enc, data+i, 8);
    encode(32, enc, (uint32_t const*)key);
    memcpy(out+i, enc, 8);
  }
  return out;
}

char *xtea_decrypt(uint8_t *data, uint8_t const *key, uint32_t len)
{
  if ((len%8) > 0)
  {
    len += 8-len%8;
  }
  char *out = malloc(len);
  uint32_t dec[2] = {0};
  for (int i = 0; i < len; i+=8)
  {
    memcpy(dec, data+i, 8);
    decode(32, dec, (uint32_t const*)key);
    memcpy(out+i, dec, 8);
  }
  return out;
}
