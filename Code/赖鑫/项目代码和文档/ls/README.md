                        编程实现简化版ls命令
# 1.项目背景：
 >   只依靠C语言的库函数来实现Linux终端简化版ls命令
# 2.项目要求
 ## i 基本要求:
    *         ls基础功能
    *         -a -l -R三个参数,并能随意组合
    *         在所有目录下都能跑  
 ## ii 附加要求:
    *         增加别的参数,增加后还能随意组合
    *         按文件类别不同输出颜色不同
    *         等等(自由发挥)
    
# 3.需求分析
3.1. 首先ls的基础功能：ls 命令将每个由 Directory 参数指定的目录或者每个由 File 参数指定的名称写到标准输出，以及您所要求的和标志一起的其它信息。如果不指定 File 或 Directory 参数， ls 命令显示当前目录的内容。

3.2  下面是-a:列出目录中所有项，包括以 .（点）开始的项和隐藏项。
 
3.3. 下面是-l选项：需要列出目录下所有内容或者该文件的详细信息，这时需要      用到stat函数来一个一个的获取.(L的小写）显示方式、链接数目、所有者、组、大小（按字节）和每个文件最近一次修改时间。如果文件是特殊文件，大小字段包含主要和次要设备数目。如果最近一次修改时间大于六个月之前，时间字段以 月份 日期 年份 的格式显示，然而六个月内修改的文件以 月份 日期 时间 的格式显示。

3.4.下面是-R选项：-R 递归列出所有子目录。

3.5.最后是在所有目录下都能跑：要求所有的目录都可以被展示出来。那么不在程序所在目录中的目录就需要切换目录才可以，这就需要用到获取当前工作目录的函数getcwd()函数和切换当前工作目录函数chdir()函数.
# 4.技术分析
4.1.首先要从输入的参数中将目录和文件名分离出来，然后切换到该目录。再使用一系列函数。

4.2.在展示-l时，需要将从函数中获得的权限的８进制数转换成我们需要的r、w、x形式

4.3.实现-R时，需要使用递归函数，并且需要不断切换目录。

# 5.主要函数：
>void myerr(const char *s,int line)   :
>>查错函数。

>　int myreadir(char *path,char ***s,int a)　：
>>获取目录所含目录名称函数

> void paixu(char **s,int l) :
>> 对所获取的目录名称进行排序函数

> void mingchengshuchu(char **s,int l) :
>>　对排序后的目录名称进行控制每行字数输出

> void quanxian(int s) :
>> 将８进制权限转换为ｒ、w、x，并输出函数

> void time1(char s[100]) :
>>将月份转换为中文，并输出时间函数

> void lllll(char s[500] ) :
>>　将获取到的目录名称以-l形式输出

> void my_printf(char s[500]) :
>> 将不同文件类型以不同颜色输出

> char panduanmulu(char s[500]) :
>> 判断文件类型函数

> int RRR(char **s,int a,int l,int len ,char mulu[500] ) :
>> -R递归函数

# 6.主要功能
直接显示：

```
 1    2    8    adaf    Adfs    bewrw    Brwe    test   
```
加参数-l：
```
drwxr-xr-x   4  sheng   sheng     4096   7月 25 16:27 1
drwxr-xr-x   2  sheng   sheng     4096   7月 25 16:26 2
drwxr-xr-x   3  sheng   sheng     4096   7月 26 17:37 8
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 adaf
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 Adfs
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 bewrw
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 Brwe
drwxr-xr-x   2  sheng   sheng     4096   7月 27 16:21 test
```
加参数-a:
```
 .    ..    1    2    8    adaf    Adfs    bewrw    Brwe    test
```
加参数-R:

```
/home/sheng/test :
 1    2    8    adaf    Adfs    bewrw    Brwe    test   
/home/sheng/test/1 :
 3    新建文件夹   
/home/sheng/test/1/3 :
 899   
/home/sheng/test/1/3/899 :
/home/sheng/test/1/新建文件夹 :
/home/sheng/test/2 :
/home/sheng/test/8 :
 555000   
/home/sheng/test/8/555000 :
/home/sheng/test/adaf :
/home/sheng/test/Adfs :
/home/sheng/test/bewrw :
/home/sheng/test/Brwe :
/home/sheng/test/test :
```
随意组合　-a、-l、-R:

```
/home/sheng/test :
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 .
drwxr-xr-x  46  sheng   sheng     4096   7月 30 19:34 ..
drwxr-xr-x   4  sheng   sheng     4096   7月 25 16:27 1
drwxr-xr-x   2  sheng   sheng     4096   7月 25 16:26 2
drwxr-xr-x   3  sheng   sheng     4096   7月 26 17:37 8
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 adaf
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 Adfs
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 bewrw
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 Brwe
drwxr-xr-x   2  sheng   sheng     4096   7月 27 16:21 test
/home/sheng/test/1 :
drwxr-xr-x   4  sheng   sheng     4096   7月 25 16:27 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
drwxr-xr-x   3  sheng   sheng     4096   7月 26 10:37 3
drwxr-xr-x   2  sheng   sheng     4096   7月 25 16:27 新建文件夹
/home/sheng/test/1/3 :
drwxr-xr-x   3  sheng   sheng     4096   7月 26 10:37 .
drwxr-xr-x   4  sheng   sheng     4096   7月 25 16:27 ..
drwxr-xr-x   2  sheng   sheng     4096   7月 26 10:37 899
/home/sheng/test/1/3/899 :
drwxr-xr-x   2  sheng   sheng     4096   7月 26 10:37 .
drwxr-xr-x   3  sheng   sheng     4096   7月 26 10:37 ..
/home/sheng/test/1/新建文件夹 :
drwxr-xr-x   2  sheng   sheng     4096   7月 25 16:27 .
drwxr-xr-x   4  sheng   sheng     4096   7月 25 16:27 ..
/home/sheng/test/2 :
drwxr-xr-x   2  sheng   sheng     4096   7月 25 16:26 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
/home/sheng/test/8 :
drwxr-xr-x   3  sheng   sheng     4096   7月 26 17:37 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
drwxr-xr-x   2  sheng   sheng     4096   7月 26 17:37 555000
/home/sheng/test/8/555000 :
drwxr-xr-x   2  sheng   sheng     4096   7月 26 17:37 .
drwxr-xr-x   3  sheng   sheng     4096   7月 26 17:37 ..
/home/sheng/test/adaf :
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
/home/sheng/test/Adfs :
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
/home/sheng/test/bewrw :
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
/home/sheng/test/Brwe :
drwxr-xr-x   2  sheng   sheng     4096   7月 28 15:36 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
/home/sheng/test/test :
drwxr-xr-x   2  sheng   sheng     4096   7月 27 16:21 .
drwxr-xr-x  10  sheng   sheng     4096   7月 28 15:36 ..
```
# 7.总结
这次写小项目时由于没有提前写规划、项目构想等东西，而是选择了直接开始写代码，这导致了后面许多问题在写好后才涌现出来，在原基础上修改了很多，浪费时间。所以，下次一定不能再这样了。还有就是，写完一个项目并且都能实现功能的成就感很强，要继续努力！



