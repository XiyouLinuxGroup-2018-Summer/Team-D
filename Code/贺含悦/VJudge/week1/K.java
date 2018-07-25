/*************************************************************************
	> File Name: K.java
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 02时27分38秒
 ************************************************************************/
import java.util.*;
public class K {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            if(a == 0 && b == 0) {
                break;
            }
            boolean flag = true;
            for(int i = a; i <= b; i++) {
                if(!isPrime(i*i+i+41)) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                System.out.println("OK");
            } else {
                System.out.println("Sorry");
            } 
        }
    }
    public static boolean isPrime(int n) {
        for(int i = 2; i <= Math.sqrt(n); i++) {
            if(n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

