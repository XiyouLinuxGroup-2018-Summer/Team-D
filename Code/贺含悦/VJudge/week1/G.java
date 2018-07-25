/*************************************************************************
	> File Name: G.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 00时50分12秒
 ************************************************************************/
import java.util.*;
public class G {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            if(a == 0 && b == 0) {
                break;
            }
            int[] arr = new int[a + 1];
            for(int i = 0; i < a; i++) {
                int n = sc.nextInt();
                arr[i] = n;
            }
            arr[a] = b;
            Arrays.sort(arr);
            for(int i = 0; i < a; i++) {
                System.out.print(arr[i] + " ");
            }
            System.out.println(arr[a]);
        }
    }
}
