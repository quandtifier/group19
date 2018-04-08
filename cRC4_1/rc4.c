#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BYTE_CONSTRAINT 256

// print the bits for debugging
void printbits(unsigned char *bits)
{
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    int j;
    for (j = 0; j < 8; j++) {
     printf("%d", !!((bits[i] << j) & 0x80));
    }
  }
  printf("Line break\n\n");
}

void printData(unsigned char data[])
{
  printf("\n\n");

  int i;
  for (i = 0; i < strlen(data); i++)
  {
    printf("%02hhx", data[i]);
  }
  printf("\n\n");
}

// RC4 KSA (key scheduling algorithm)
void ksa(char *k, unsigned char *s)
{
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    s[i] = i;
  }
  int klen = strlen(k);
  int j = 0;
  for (i = 0; i < BYTE_CONSTRAINT; i++)
  {
    j = (j + s[i] + k[i % klen]) % BYTE_CONSTRAINT;
    unsigned char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}


// RSA PGRA (psuedo-random generation algorithm)
void pgra(unsigned char k[], unsigned char s[], unsigned char in[], unsigned char out[])
{
  int i,j,n;
  i=j=n=0;
  for (;n < strlen(in); n++)
  {
    i = (i + 1) % BYTE_CONSTRAINT;
    j = (j + s[i]) % BYTE_CONSTRAINT;
    unsigned char c = s[i];
    s[i] = s[j];
    s[j] = c;
    out[n] = s[(s[i] + s[j]) % BYTE_CONSTRAINT] ^ in[n];
  }
}

int main(int argc, char *argv[])
{
  // structure for the command line args
  if( argc == 3 ) {
     printf("The key supplied is:  %s\n\n", argv[2]);
     printf("The text supplied is:  %s\n\n", argv[1]);
  }
  else if( argc > 3 ) {
     printf("Too many arguments supplied.\n");
     return -1;
  }
  else if(argc < 3){
     printf("Two arguments expected: [<plaintext>.txt] [key string up to 127 chars]\n");
     return -1;
  }
  // open the plaintext file
  FILE *fptr = fopen(argv[1], "r");
  fseek(fptr, 0, SEEK_END);
  int fsize = ftell(fptr);
  fseek(fptr, 0, SEEK_SET); //rewinds

  // read plaintext and make reference
  char *pt = malloc(fsize + 1);
  fread(pt, fsize, 1, fptr);
  fclose(fptr);
  pt[fsize] = 0;
  // get the key from the commandline
  char *key = argv[2];
  // the bytes that start out as 0x00 and go through 0xFF
  unsigned char bytes[BYTE_CONSTRAINT];

  // the first (encryption) run of RC4
  ksa(key, bytes);
  unsigned char *ct = malloc(sizeof(int) * strlen(pt));
  pgra(key, bytes, pt, ct);

  printf("The original data:\n\n");
  printData(pt);
  printf("The encrypted data:\n\n");
  printData(ct);

  unsigned char *pt2 = malloc(sizeof(int) * strlen(ct));
  ksa(key, bytes);
  pgra(key, bytes, ct, pt2);

  printf("The decrypted data:\n\n");
  printData(pt2);

  return 0;
}
