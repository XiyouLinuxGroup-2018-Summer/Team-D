/*************************************************************************
	> File Name: C.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 00时02分47秒
 ************************************************************************/

import java.util.*;
public class C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        while(n-->0) {
            String s = sc.nextLine();
            if(new StringBuffer(s).reverse().toString().equals(s)) {
                System.out.println("yes");
            } else {
                System.out.println("no");
            }
        }
    }
}
