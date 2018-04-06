#include <stdio.h>
#include <string.h>

#define BYTE_CONSTRAINT 256

void printbits(unsigned char bits[])
{
  // print the bits for debugging
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    int j;
    for (j = 0; j < 8; j++) {
     printf("%d", !!((bits[i] << j) & 0x80));
    }
  }
  printf("Line break\n\n");
}

void ksa(char k[], unsigned char s[])
{
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    s[i] = i;
  }
  printbits(s);

  // RC4 KSA (key scheduling algorithm)
  int j = 0;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    j = (j + s[i] + k[i % strlen(k)]) % BYTE_CONSTRAINT;
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int main()
{
   char *key = "HelloRC4c";
   printf(key);
   printf("\n");
   // the bytes that start out as 0x00 and go through 0xFF
   unsigned char bytes[BYTE_CONSTRAINT];

   ksa(key, bytes);

   printbits(bytes);
   // RSA PGRA (psuedo-random generation algorithm)
   int i,j,n;
   i=j=n=0;
   unsigned char out[256];
   for (n = 0; n < strlen(key); n++) {
     i = (i + 1) % BYTE_CONSTRAINT;
     j = (j + bytes[i]) % BYTE_CONSTRAINT;
     char c = bytes[i];
     bytes[i] = bytes[j];
     bytes[j] = c;
     out[n] = bytes[(bytes[i] + bytes[j]) % BYTE_CONSTRAINT];
   }

   printbits(out);
}

   // // for debugging check to ensure no duplicates valued bytes
   // for (i = 0; i < BYTE_CONSTRAINT; i++) {
   //   int j;
   //   for (j = 0; j < BYTE_CONSTRAINT; j++) {
   //      if (bytes[i] == bytes[j] && i != j) {
   //        printf("something went wrong there are dupicates!!!");
   //      }
   //   }
   // }
   // return 0;
