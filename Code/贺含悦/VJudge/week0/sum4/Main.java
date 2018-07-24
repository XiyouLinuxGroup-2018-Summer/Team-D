/*************************************************************************
	> File Name: Main.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月21日 星期六 17时55分51秒
 ************************************************************************/

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            int n = sc.nextInt();
            if(n == 0)
                break;
            int sum = 0;
            while(n-->0) {
                int a = sc.nextInt();
                sum += a;
            }
            System.out.println(sum);
        }
        sc.close();
    }
}
