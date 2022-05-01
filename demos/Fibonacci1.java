import java.lang.String;

public class Fibonacci1 {
    /*
    A fibonacci demo implemention, aim to test array
    */

    public static void main(String[] args) {
        int maxn = 80;
        //init
        long[] a = new long[maxn];
        a[0] = 0;
        a[1] = 1;
        
        for(int i = 2; i < maxn; i++) {
            a[i] = a[i - 1] + a[i - 2];
            System.out.println(a[i]);
        }
    }
}