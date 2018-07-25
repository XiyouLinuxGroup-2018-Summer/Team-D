/*************************************************************************
	> File Name: F.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 00时44分56秒
 ************************************************************************/
import java.util.*;
public class F {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        while(n-- > 0) {
            String line = sc.nextLine();
            char[] chs = line.toCharArray();
            int number = 0;
            for(int i = 0; i < chs.length; i++) {
                if(Character.isDigit(chs[i])) {
                    number++;
                }
            }
            System.out.println(number);
        }
    }
}

