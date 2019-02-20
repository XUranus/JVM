import java.lang.String;

public class Sum {
    /*test loop */
    public static void main(String[] args) {
        long sum = 0;
        for(int i=0;i<=10000;i++) {
            sum += i;
        }
        System.out.println(sum);
    }
}