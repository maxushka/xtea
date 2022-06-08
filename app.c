#include "xtea.h"
#include <stdio.h>

void print_error(char *err)
{
  printf("%s\n", err);
  printf("Please, use:\n");
  printf("\txtea -e file_in file_out\t(to encryption file)\n");
  printf("\txtea -d file_in file_out\t(to decryption file)\n");
  printf("\txtea -pd file_in file_out bytes_count\t(to decryption part of file)\n");  
}

uint8_t key[] = {
    0x54, 0x49, 0x31, 0x38, 
    0x32, 0x34, 0x33, 0x35,
    0x36, 0x37, 0x33, 0x34, 
    0x39, 0x31, 0x53, 0x5f
};

int main(int argc, char const *argv[])
{
  if (argc < 4)
  {
    print_error("Few arguments");
    exit(0);
  }

  FILE *in_file  = fopen(argv[2], "r"); 
  FILE *out_file = fopen(argv[3], "w"); 
  if (in_file == NULL || out_file == NULL) 
  {   
    printf("Error! Could not open file\n"); 
    exit(-1);
  } 

  if (strcmp(argv[1], "-e") == 0)
  {
    char *line = malloc(8);
    if (line)
    {
      while(fread(line, 1, 8, in_file) != 0)
      {
        char *out = encrypt(line, key);
        fwrite(out, 1, 8, out_file);
        free(out); 
      }
      free(line);
    }
  }
  else if (strcmp(argv[1], "-d") == 0)
  {
    char *line = malloc(8);
    if (line)
    {
      while (fread(line, 1, 8, in_file) != 0) 
      {
        char *out = decrypt(line, key, 8);
        fwrite(out, 1, 8, out_file);
        free(out); 
      }
      free(line);
    }
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
    len += (len%8 > 0) ? (8-len%8):0;
    char *line = malloc(len);
    if (line)
    {
      fread(line, 1, len, in_file);
      char *out = decrypt(line, key, len);
      fwrite(out, 1, len, out_file);
      free(out); 
      free(line);
    }
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
