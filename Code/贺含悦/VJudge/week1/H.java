/*************************************************************************
	> File Name: H.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 01时02分45秒
 ************************************************************************/

import java.util.*;
public class H {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        while(n-- > 0) {
            String s = sc.nextLine();
            char chs[] = s.toCharArray();
            boolean flag = true;
            for(int i = 1; i < chs.length; i++) {
                if(!(Character.isUpperCase(chs[0]) || Character.isLowerCase(chs[0]) || chs[0] == '_')) {
                    flag = false;
                    break;
                }
                if(!(Character.isUpperCase(chs[i]) || Character.isLowerCase(chs[i]) || Character.isDigit(chs[i]) || chs[i] == '_')) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                System.out.println("yes");
            } else {
                System.out.println("no");
            }
        }
    }
}
