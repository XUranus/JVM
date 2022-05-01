public class ThrowTest {

    /**
     * Test Exception throw
     */
    public static void main(String[] args) {
        foo(args);
    }

    private static void foo(String[] args) {
        try {
            bar(args);
        } catch (NumberFormatException e) {
	        e.printStackTrace();
        }
    }

    private static void bar(String[] args) {
        if(args.length == 0) {
            throw new IndexOutOfBoundsException("no args!");
        }
        int x = Integer.parseInt(args[0]);
        System.out.println(x);
    }
}
