/*************************************************************************
	> File Name: Main.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月21日 星期六 17时51分43秒
 ************************************************************************/

import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            if(a == 0 && b == 0)
                break;
            System.out.println(a + b);
        }
        sc.close();
    }
}
