public class Fibonacci3 {
    /*
    * A fibonacci demo aim to test method invocation
    */

    private static final int maxn = 80;
    private static long[] fibo = new long[maxn];

    public static void main(String[] args) {
        fibo[0] = 0;
        fibo[1] = 1;
        for(int i = 2; i < maxn; i++) {
            fibo[i] = fibo[i - 1] + fibo[i - 2];
        }
        for(int i = 1; i < maxn; i++) {
            printFibonacci(i);
        }
    }

    private static void printFibonacci(int index) {
        System.out.println("fibonacci[" + index + "] = " + fibo[index]);
    }
}