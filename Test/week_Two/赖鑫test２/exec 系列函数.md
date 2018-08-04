* int execv(const char * path,char * const envp[ ]);

>path是路径名，envp是环境变量，该函数通过路径名方式调用可执行文件作为新的程序映像

* int execve(const char * path,char * const agrv[ ],char * const envp[ ]);

>系统调用，path是路径名，argv是命令行参数，envp是环境变量

* int execl(const char * path,const char * arg,...);

>路径名方式调用，arg必须为单独参数

* int execle(const char * path,const char * arg,...);

>路径名方式调用，arg必须为单独参数，且环境变量必须位于arg最后一个参数的后面

* int exevp(const char * file,char * const agrv[ ]);

>通过路径名方式调用，file若包含'/',就是路径名，不包含，到环境变量定义目录中寻找可执行文件

* int execlp(const char * file,const char * arg,...);

>路径名方式调用，arg必须为单独参数，file若包含'/',就是路径名，不包含，到环境变量定义目录中寻找可执行文件