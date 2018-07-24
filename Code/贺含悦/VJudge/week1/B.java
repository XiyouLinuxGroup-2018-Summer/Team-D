/*************************************************************************
	> File Name: B.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 23时47分01秒
 ************************************************************************/

import java.util.*;
public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            double r = sc.nextDouble();
            System.out.printf("%.3f\n", 4/3.0*r*r*r*3.1415927);
        }
    }
}
