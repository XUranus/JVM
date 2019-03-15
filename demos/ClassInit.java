public class ClassInit {
    private int a;
    public static int b = 10;

    public ClassInit() {
        a = 10;
    }

    public static void main(String[]args) {
        int aa = new ClassInit().a;
        System.out.println(aa);
    }
} 