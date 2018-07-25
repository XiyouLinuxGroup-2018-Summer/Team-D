/*************************************************************************
	> File Name: Main.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月21日 星期六 18时01分38秒
 ************************************************************************/

import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while(n-->0) {
            int x = sc.nextInt();
            int sum = 0;
            while(x-->0) {
                int a = sc.nextInt();
                sum += a;
            }
            System.out.println(sum);
        }
        sc.close();
    }
}
