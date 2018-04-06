//import java.util.*;

public class RC4 {
  // length of 'word' for the RC4 algorithm
  public static final int BYTE_CONSTRAINT = 256;

  // permute the byte array in occordance with RC4
  public static byte[] permute(byte[] theBytes) {
    if (theBytes.length != BYTE_CONSTRAINT) {
      return theBytes;
    }
    int i = 0;
    int j = 0;
    for (int n = 0; n < BYTE_CONSTRAINT; n++) {
      i = (i + 1) % BYTE_CONSTRAINT;
      j = (j + theBytes[i]) % BYTE_CONSTRAINT;
      byte b = theBytes[i];
      theBytes[i] = theBytes[j];
      theBytes[j] = b;
      //theBytes[n] = ((theBytes[i] + theBytes[j])) % BYTE_CONSTRAINT;
    }
    return theBytes;
  }



  public static void main(String[] args) {
    // the string that we will randomize
    String key = "HelloRC4";
    System.out.println(key);
    // the array to be randomized
    byte[] bytes = new byte[256];
    for (int i = 0; i < BYTE_CONSTRAINT; i++) {
      bytes[i] = (byte) i; // store the chars as bytes
    }
    // check the initialization
    for (int i = 0; i < BYTE_CONSTRAINT; i++) {
      System.out.print(((int) bytes[i]) + ",");
    }
    System.out.println();
    int j = 0;
    for (int i = 0; i < BYTE_CONSTRAINT; i++) {

      j = (j + bytes[i] + key.charAt(i % key.length())) % BYTE_CONSTRAINT;
      byte b = bytes[i];
      bytes[i] = bytes[j];
      bytes[j] = b;
    }

    for (int i = 0; i < BYTE_CONSTRAINT; i++) {
      System.out.print(((int) bytes[i]) + ",");
    }

    //byte[] newBytes = permute(bytes);

    // check the result
    for (int i = 0; i < BYTE_CONSTRAINT; i++) {
      //System.out.print(((int) newBytes[i]) + ","); // store the chars as bytes
    }

  }
}
