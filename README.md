# xtea

eXtended TEA is a block cipher designed to correct weaknesses in TEA

## Application usage

#### Compile

`git clone https://github.com/maxushka/xtea.git`

`cd xtea`

`make`

#### Usage

To encryption file:

`xtea -e file_in file_out`

To decryption file:

`xtea -d file_in file_out`

To decryption part of file:

`xtea -pd file_in file_out bytes_count`

## Library usage

```c
#include "xtea.h"

const uint8_t key[] = {0x54, 0x49, 0x31, 0x38, 0x32, 0x34, 0x33, 0x35,
                       0x36, 0x37, 0x33, 0x34, 0x39, 0x31, 0x53, 0x5f};

int main(void)
{
  char *test_str = "Hello, world!";

  char *enc_str = xtea_encrypt(test_str, key);

  char *dec_str = xtea_decrypt(test_str, key, strlen(test_str));

  printf("Source text: %s\n", test_str);
  printf("Encoded text: %s\n", enc_str);
  printf("Decoded text: %s\n", dec_str);

  free(enc_str);
  free(dec_str);

  return 0;
}
```