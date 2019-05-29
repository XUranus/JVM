public class Fibonacci3 {
    /*
    this is a fibonacci demo aim to test string,method invoke
     */

    public static void main(String[] args) {
        int maxn = 80;
        long[] fibo = new long[maxn];
        fibo[0] = 0;
        fibo[1] = 1;
        for(int i=2;i<maxn;i++)
            fibo[i] = fibo[i-1] + fibo[i-2];
        for(int i=1;i<maxn;i++)
            printFibonacci(i,fibo[i]);
    }

    private static void printFibonacci(int index,long value) {
        System.out.print("fibonacci[");
        System.out.print(index);
        System.out.print("]=");
        System.out.print(value);
        System.out.println("");
    }
}