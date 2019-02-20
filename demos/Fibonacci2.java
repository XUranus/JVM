public class Fibonacci2 {
    /*this is a fibonacci demo implemnent by recursion,
    n>10 may cause java stack overflow error.
    aim to test method invoke */
    public static void main(String[] args) {
        for(int i=1;i<10;i++)
            System.out.println(fibonacci(i));
    }

    private static int fibonacci(int n) {
        if(n <= 1)
            return n;
        return fibonacci(n-1) + fibonacci(n-2);
    }
}