struct strange {
    char a, b, c, d, e, zero;                      /*这是一个结构体，成员为char型*/
};

int main(int argc, char *argv[])
{
    struct strange xp[3];                         //声明一个struct strange型数组
    int characters[6] = "abcde";                  
    for (int i = 0; i < 6; i++) {
        *((char *)(xp + 0) + i) = characters[i];    //将数组characters[6]中的每个元素赋值给xp[0]的元素
    }

    strcpy((char *)&xp[1], (char *)characters);     //将字符串拷贝到xp[1]上
    memcpy(&xp[2], characters, sizeof(struct strange));    //将characters成员拷贝到xp[2]
    printf("%zu\n", strlen((char *)characters));     //输出characters的长度

    for (int i = 0; i < 3; i++) {        //输出结构体数组中每个元素里e的字符
        printf("%c\n", xp[i].e);
    }
}
