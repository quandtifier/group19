import java.util.ArrayList;
import java.util.Random;

public class Rand {

    public static long a;
    public static long b;
    public static long m;
    public static long previous;

    public static void main(final String[] theArgs) {
        seed(10);
        for (int i = 0; i < 25; i++) {
            System.out.println(rand());
        }
    }

    //Initialize the seed.
    public static void seed(final long seed) {
        previous = (int) seed;
    }

    //Generate random number.
    public static long rand () {
        a = random23Bits();
        b = random23Bits();
        m = random23Bits();
        previous = (a * previous + b) % m;
        return previous;
    }

    //Generate random 32 bits.
    public static long random23Bits() {
        StringBuilder s = new StringBuilder();
        Random r = new Random();
        for (int i = 0; i < 32; i++) {
            s.append(r.nextInt(2));
        }
        return Long.parseUnsignedLong(s.toString(), 2);
    }
}
