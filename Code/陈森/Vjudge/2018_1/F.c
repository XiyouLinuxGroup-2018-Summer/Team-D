/*
 * @filename:    F.c
 * @author:      Crow
 * @date:        07/23/2018 09:22:54
 * @description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char str[1000];
    int num, res;

    scanf("%d", &num);
    getchar();
    while (num--) {
        scanf("%s", str);
        getchar();
        res = 0;
        for (int i = 0; i < strlen(str); ++i)
            if (str[i] >= '0' && str[i] <= '9')
                res++;
        printf("%d\n", res);
    }

    return 0;
}
