## 1.项目背景
用c语言实现自己的简化版 shell　

## 2.项目要求
### 基本要求
> * 支持命令的各种参数
> * 支持输入输出重定向(>, >>, <)
> * 支持管道 ( 即 | )
> * 支持后台运行 ( 即 & )
> * 让自己的shell支持内建命令,实现cd即可
> * Ctrl + c不能中断自己的shell
> * 界面美观,输出整齐
### 进阶需求
> * 实现Tab补全命令以及历史记录(即,可以上下翻历史命令)
> > >提示:使用 readline库
> * 让自己的shell可以像bash, zsh一样运行
> > >提示: 设置环境变量
> * 自由发挥,加你想加的功能


## 3.需求分析
3.1　首先是支持各种命令的各种参数，需要在命令文件里去找。

3.2　支持输入输出重定向和管道，但是只能支持这４种里的一种，即若输入命令中有两种或两种以上，那么程序不支持运行这种命令。

3.3　后台运行符得单独处理。

3.4　cd命令也需要单独处理。
## 4.技术分析
4.1　需要进行转化处理，使输入进来的字符串命令变成字符指针数组，便于从从几个目录中寻找命令中的可执行程序。

4.2　需要对已转化的字符指针数组命令进行解析，分别处理，并且计算特殊命令符的数量，多于１个特殊命令符不做处理，给出提示信息。

4.3　由解析出的结果对输入输出重定向和管道特殊命令符分别处理。

4.4　判断每个输入命令结尾是否有后台运行符，作出标记，在进程部分根据标记作出判断，分开处理。

4.4　cd切换目录功能属于自建命令需要单独处理实现。

4.5　Tab补全命令以及历史记录（上下键翻历史命令）需要外部库函数，readline。

4.6　Ctrl + c不能中断自己的shell，让程序屏蔽掉该命令即可。
## 5.主要函数
> void my_printf(char path[100]);
>> 输出提示符和显示当前目录函数。

>int part(char *buf,char s[100][256]) ;
>> 将输入的一维字符串转化为二维字符串数组函数。

>void explain(char s[100][256],int len);
>>将二维字符串数组变为字符指针数组并且遍历、标记，然后单独处理函数。

>int find(char *command);
>>查找命令中的可执行程序函数。
## 6.主要功能
基本命令：

```
/home/sheng  My Shell : ls test
1  2  8  adaf  Adfs  bewrw  Brwe  test
```
输出重定向：

```
/home/sheng  My Shell : ls test > a
/home/sheng  My Shell : cat a
1
2
8
adaf
Adfs
bewrw
Brwe
test
```
输出重定向（追加）：

```
/home/sheng  My Shell : ls test > a
/home/sheng  My Shell : ls test >> a
/home/sheng  My Shell : cat a
1
2
8
adaf
Adfs
bewrw
Brwe
test
1
2
8
adaf
Adfs
bewrw
Brwe
test
```
输入重定向：

```
/home/sheng  My Shell : wc -c < a
64
```
管道命令：

```
/home/sheng  My Shell : ls -l / | wc -c
1575
```
cd切换目录命令：

```
/home/sheng  My Shell : cd test
/home/sheng/test  My Shell : ls
1  2  8  adaf  Adfs  bewrw  Brwe  test
```
Tab自动补全：

```
/home/sheng  My Shell : c
c.c             ceshi/          content.jar     content.xml.xz  
```
## 7.总结
　这次的小项目对比上次简单明了了很多，思路很清晰，代码也不是很长，实现起来相对容易一点。
　
　但是通过这次的小项目my shell的编写，感觉到自己对于Linux的一些基础命令掌握的不是很好，需要再加强。