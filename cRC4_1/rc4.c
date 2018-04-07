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



// RC4 KSA (key scheduling algorithm)
void ksa(char *k, unsigned char *s)
{
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    s[i] = i;
  }
  printf(k);
  printbits(s);// look at the bits in order
  int klen = strlen(k);
  int j = 0;
  for (i = 0; i < BYTE_CONSTRAINT; i++)
  {
    j = (j + s[i] + k[i % klen]) % BYTE_CONSTRAINT;
    unsigned char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
  printf(k);
  printbits(s);
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

int main()
{
  char *key = "This is the Key";
  char *pt = "This is some plaintext";
  printf(pt);
  printf("\n");
  // the bytes that start out as 0x00 and go through 0xFF
  unsigned char bytes[BYTE_CONSTRAINT];

  ksa(key, bytes);

  printbits(bytes);

  unsigned char *ct = malloc(sizeof(int) * strlen(pt));
  pgra(key, bytes, pt, ct);

  printbits(ct);
  int i;
  for (i = 0; i < strlen(pt); i++)
  {
    printf("%02hhx", ct[i]);
  }
  printf("\n\n");
  printf(ct);
  printf("\n\n");
  unsigned char *pt2 = malloc(sizeof(int) * strlen(ct));
  pgra(key, bytes, ct, pt2);
  printf(pt2);
  printf("\n");

  printf("\n\nhello from end of file!!\n\n");
  return 0;
}
