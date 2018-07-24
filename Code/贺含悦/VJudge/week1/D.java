/*************************************************************************
	> File Name: D.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 00时13分55秒
 ************************************************************************/

import java.util.*;
public class D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            System.out.println(min(a, b));
        }
    }
    public static int max(int m, int n) {
        if(m < n) {
            n = (m + n) - (m = n);
        }
        if(m % n == 0) {
            return n;
        }
        return max(n, m%n);
    }
    public static int min(int m, int n) {
        return m*n/max(m, n);
    }
}
