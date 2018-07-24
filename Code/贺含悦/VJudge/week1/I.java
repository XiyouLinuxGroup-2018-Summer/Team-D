/*************************************************************************
	> File Name: I.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 01时44分59秒
 ************************************************************************/
import java.util.*;
public class I {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while(n-- > 0) {
            double a = sc.nextDouble();
            double b = sc.nextDouble();
            double c = sc.nextDouble();
            if(a+b>c && a+c>b && b+c>a) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}

