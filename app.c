#include "xtea.h"
#include <stdio.h>

const uint8_t key[] = {0x54, 0x49, 0x31, 0x38, 0x32, 0x34, 0x33, 0x35,
                       0x36, 0x37, 0x33, 0x34, 0x39, 0x31, 0x53, 0x5f};

void encode_file(FILE *fi, FILE *fo)
{
  char *line = malloc(8);

  if (line)
  {
    while (fread(line, 1, 8, fi) != 0)
    {
      char *out = xtea_encrypt(line, key, 8);
      fwrite(out, 1, 8, fo);
      free(out);
      memset(line, 0xff, 8);
    }
    free(line);
  }
}

void decode_file(FILE *fi, FILE *fo)
{
  char *line = malloc(8);
  uint32_t len = 0, count = 0;

  if (line)
  {
    while (fread(line, 1, 8, fi) != 0)
    {
      char *out = xtea_decrypt(line, key, 8);
      fwrite(out, 1, 8, fo);
      free(out);
    }
    free(line);
  }
}

void decode_part_file(FILE *fi, FILE *fo, uint32_t len)
{
  char *line = malloc(len);
  if (line)
  {
    fread(line, 1, len, fi);
    char *out = xtea_decrypt(line, key, len);
    fwrite(out, 1, len, fo);
    free(out);
    free(line);
  }
}

void print_error(char *err)
{
  printf("%s\n", err);
  printf("Please, use:\n");
  printf("\txtea -e file_in file_out\t(to encryption file)\n");
  printf("\txtea -d file_in file_out\t(to decryption file)\n");
  printf("\txtea -pd file_in file_out bytes_count\t(to decryption part of "
         "file)\n");
}

int main(int argc, char const *argv[])
{
  if (argc < 4)
  {
    print_error("Few arguments");
    exit(0);
  }

  FILE *in_file = fopen(argv[2], "rb");
  FILE *out_file = fopen(argv[3], "wb");
  if (in_file == NULL || out_file == NULL)
  {
    printf("Error! Could not open file\n");
    exit(-1);
  }

  if (strcmp(argv[1], "-e") == 0)
  {
    encode_file(in_file, out_file);
  }
  else if (strcmp(argv[1], "-d") == 0)
  {
    decode_file(in_file, out_file);
  }
  else if (strcmp(argv[1], "-pd") == 0)
  {
    if (argc < 5)
    {
      print_error("Few arguments");
      fclose(in_file);
      fclose(out_file);
      exit(0);
    }

    uint32_t len = strtol(argv[4], NULL, 10);
    len += (len % 8 > 0) ? (8 - len % 8) : 0;

    decode_part_file(in_file, out_file, len);
  }
  else
  {
    print_error("Wrong parametr");
    fclose(in_file);
    fclose(out_file);
    exit(-1);
  }

  fclose(in_file);
  fclose(out_file);
  return 0;
}
