/*************************************************************************
	> File Name: L.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 01时54分03秒
 ************************************************************************/
import java.util.*;
public class L {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            String s = sc.nextLine();
            char[] chs = s.toCharArray();
            for(int i = 0; i < chs.length-1; i++) {
                chs[0] = Character.toUpperCase(chs[0]);
                if(chs[i] == ' ') {
                    chs[i+1] = Character.toUpperCase(chs[i+1]);
                }
            }
            System.out.println(String.valueOf(chs));
        }
    }
}

