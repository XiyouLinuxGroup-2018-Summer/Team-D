/*************************************************************************
	> File Name: Main.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月21日 星期六 17时45分29秒
 ************************************************************************/

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while((n--)>0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            System.out.println(a + b);
        }
        sc.close();
    }
}
