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
void ksa(char k[], unsigned char s[])
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
char* pgra(char k[], unsigned char s[], unsigned char out[])
{
  int i,j,n;
  i=j=n=0;
  for (n = 0; n < strlen(k); n++) {
    i = (i + 1) % BYTE_CONSTRAINT;
    j = (j + s[i]) % BYTE_CONSTRAINT;
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
    out[n] = s[(s[i] + s[j]) % BYTE_CONSTRAINT];
  }
  return out;
}


int main(int argc, char *argv[])
{
  if (argc < 3) {
    return -1;
  }
  // the bytes that start out as 0x00 and go through 0xFF
  unsigned char bytes[BYTE_CONSTRAINT];
  // key scheduling algorithm
  ksa(arg[1], bytes);

  printbits(bytes);

  unsigned char result = malloc(sizeof(char, * argv[2]));
  // psuedo-random generation algorithm
  pgra(key, argv[2], result);

  printbits(result);
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
