/*************************************************************************
	> File Name: E.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 00时21分11秒
 ************************************************************************/

import java.util.*;
public class E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while(n-->0) {
            char c = sc.next().charAt(0);
            int a = sc.nextInt();
            int b = sc.nextInt();
            if(c == '+') {
                System.out.println(a + b);
            } else if(c == '-') {
                System.out.println(a - b);
            } else if(c == '*') {
                System.out.println(a * b);
            } else {
                if(a % b == 0) {
                    System.out.println(a / b);
                } else {
                    System.out.format("%.2f", a*1.0/b).println();
                }
            }
        }
    }
}
