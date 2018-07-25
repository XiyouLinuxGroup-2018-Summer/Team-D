/*************************************************************************
	> File Name: J.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 02时06分40秒
 ************************************************************************/
import java.util.*;
public class J {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while(n-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            if(a == zhenYue(b) && b == zhenYue(a)) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
    public static int zhenYue(int n) {
        int sum = 0;
        for(int i = 1; i <= n/2; i++) {
            if(n % i == 0) {
                sum += i;
            }
        }
        return sum;
    }
}
