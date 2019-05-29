public class BubbleSort {
    /*
    this class is a buble sort demo, aim to test array
     */
    public static void main(String[] args) {
        int[] arr={16,3,8,34,41,22,9,1,4,23,6,4,3,23};
        
        for(int i=0;i<arr.length-1;i++){
            for(int j=0;j<arr.length-1-i;j++){
                if(arr[j]>arr[j+1]){
                    int temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        }
        for(int num:arr)
            System.out.println(num);
    }
}