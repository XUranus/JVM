import java.lang.String;

public class Fibonacci1 {
    /*
    this ia a fibonacci demo implement by array iteration,
    aim to test array
     */

    public static void main(String[] args) {
        int maxn = 80;
        long[] a = new long[maxn];
        a[0] = 0;
        a[1] = 1;
        //init
        for(int i=2;i<maxn;i++) {
            a[i] = a[i-1] + a[i-2];
            System.out.println(a[i]);
        }
    }
}