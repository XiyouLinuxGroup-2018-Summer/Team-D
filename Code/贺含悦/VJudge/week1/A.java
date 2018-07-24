/*************************************************************************
	> File Name: 1.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月23日 星期一 23时40分09秒
 ************************************************************************/

import java.util.*;
public class A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            String line = sc.nextLine();
            char[] chs = line.toCharArray();
            Arrays.sort(chs);
            System.out.println(chs[0] + " " + chs[1] + " " + chs[2]);
        }
    }
}
