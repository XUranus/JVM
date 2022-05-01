public class Fibonacci2 {
    /*
    * A fibonacci demo implemnent by recursion,
    * aim to test method invoke 
    */
    public static void main(String[] args) {
        for(int i=1;i<10;i++)
            System.out.println(fibonacci(i));
    }

    private static int fibonacci(int n) {
        if(n <= 1) {
            return n;
        } else {
            return fibonacci(n - 1) + fibonacci(n - 2);
        }
    }
}