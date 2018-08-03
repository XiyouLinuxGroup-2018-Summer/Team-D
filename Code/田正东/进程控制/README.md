# **第二周项目**
---------------------------------------------------------
## 项目名称
- 实现自己的shell

---------------------------------------------------------
## 项目要求
- 支持命令的各种参数                       （已完成）
- 支持输入输出重定向(>, >>, <)             （已完成）
- 支出管道 ( 即 | )                       （已完成）
- 支持后台运行 ( 即 & )                    （已完成）
- 让自己的shell支持内建命令,实现cd即可       （已完成）
- Ctrl + c不能中断自己的shell             （已完成）
- 界面美观,输出整齐                         （已完成）

---------------------------------------------------------
## 附加要求
- 实现Tab补全命令以及历史记录(即,可以上下翻历史命令)    （已完成history命令和文件补全）
- 让自己的shell可以像bash, zsh一样运行
- 等等（自由发挥）
---------------------------------------------------------
## 开发者
- 田正东

---------------------------------------------------------
## 项目环境
- Ubuntu 18.04(编辑器：vim)

---------------------------------------------------------
## 开发思路
- 根据输入命令，解析参数，然后再fork一个进程，在进程中利用execvp运行外部命令，其cd命令根据chdir()函数实现，tab补全和历史利用readdir()函数及库实现。Ctrl+c采用信号中断实现

---------------------------------------------------------
## 主要函数
- void explain_input(char *buf,int *argcount,char arglist[100][256])

       函数功能：解析buf中存放的命令，把每个选项存放在arglist中

- void get_input(char *buf,char *path,int *his_count,char history[][256])

       函数功能：获得一条用户输入的待执行的命令。参数buf用于存放输入的命令。如果命令过长，则终止程序，输入的命令以换行符“\n”作为结束标志；打印myshell的提示符以及进程所在路径；存储历史命令并记数

- int find_command(char *command)

       函数功能：分别在当前目录下、/bin、/usr/bin目录下查找命令的可执行程序

-  void do_cmd(int argcount,char arglist[100][256],int his_count,char history[][256])

       函数功能：命令分类并执行存放在arglist中的命令


---------------------------------------------------------
## 注意点
- 因为用了readline库，因为这是一个动态库，所以在链接时要对其进行链接

---------------------------------------------------------
## 处理流程
- 分配动态存储空间
- 进入while(1)循环
- 打印shell提示符
- 输入命令
- 判断是否为exit或logout，若是则释放动态分配的空间然后结束
- 若不是则解析输入的命令
- 执行输入的命令
- 返回while(1)

---------------------------------------------------------
## 功能展示
- 先用makefile编译然后运行


![先用makefile编译然后运行](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6t83iwtj30n503kad1.jpg)

- ls -l /tmp

![ls -l /tmp](https://wx3.sinaimg.cn/mw1024/0078LA9Uly1ftv6t8ax4aj30w8072gwf.jpg)

- 重定向 >

![重定向 >](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r3fzucj30oa0ei16m.jpg)

- >>

![>>](https://wx1.sinaimg.cn/mw1024/0078LA9Uly1ftv6r4wdc3j30xf0istvv.jpg)
![>>](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2qvbkj30wd02uzn2.jpg)

- <

![<](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2idikj30g8015glz.jpg)

- 管道

![管道](https://wx1.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2hdnpj30he00z3yt.jpg)

- 后台&

![后台&](https://wx4.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2qlcxj30io02dgmo.jpg)

- 退出

![退出](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2f7dtj30er01a74o.jpg)
![退出](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2e9trj30f4013mxi.jpg)

- 错误命令

![错误命令](https://wx2.sinaimg.cn/mw1024/0078LA9Uly1ftv6r2e9trj30f4013mxi.jpg)

----------------------------------------------------------
## 总结
- 这是留校的第二个项目。看了看书上的模板感觉比上周要复杂一些，因为管道重定向之类的命令已经完成了，在此基础上加上cd，history，补全，颜色，>>,信号中断等等功能就完成了,因为用了readline动态库，所以自己写了个makefile把动态库连接上。