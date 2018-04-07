#include <stdio.h>
#include <string.h>

#define BYTE_CONSTRAINT 256

// print the bits for debugging
void printbits(unsigned char bits[])
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
void ksa(unsigned char k[], unsigned char s[])
{
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    s[i] = i;
  }
  printbits(s);// look at the bits in order
  int j = 0;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    j = (j + s[i] + k[i % strlen(k)]) % BYTE_CONSTRAINT;
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}


// RSA PGRA (psuedo-random generation algorithm)
void pgra(unsigned char k[], unsigned char s[], unsigned char in[], unsigned char out[])
{
  int i,j,n;
  i=j=n=0;
  for (n = 0; n < strlen(k); n++) {
    i = (i + 1) % BYTE_CONSTRAINT;
    j = (j + s[i]) % BYTE_CONSTRAINT;
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
    out[n] = s[(s[i] + s[j]) % BYTE_CONSTRAINT] ^ in[n];
  }
}

int main()
{
   char *key = 0x0102030405;
   char *pt = "Encript this text with rc4.";
   printf(key);
   printf("\n");
   // the bytes that start out as 0x00 and go through 0xFF
   unsigned char bytes[BYTE_CONSTRAINT];

   ksa(key, bytes);

   printbits(bytes);

   unsigned char ct[BYTE_CONSTRAINT];
   pgra(key, bytes, pt, ct);

   printbits(output);
   int i;
   for (i = 0; i < strlen(pt); i++)
   {
     printf("%02hhX", ct[i]);
   }

   printf("\n\nhello from end of file!!\n\n");
   return 0;
}
