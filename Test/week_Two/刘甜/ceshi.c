c语言
printf("%d\n",&(&4[(int *)3])[5]);  //

linux进程操作简答题
3. 简要说明 exec系列函数
    exec系列函数有6种不同的调用的形式，无论是哪一个，都是将可执行程序的路径、命令行参数和环境变量3个参数传递给可执行程序main函数
   它们的声明及其定义如下：
    #include <unistd.h>

       extern char **environ;

       int execl(const char *path, const char *arg, .../* (char  *) NULL */);
        path:可执行文件的文件名，包括路径名会，文件名默认在系统环境变量PATH中寻找，如果给定文件路径名，则找这个文件.argv参数是一个以NULL结尾的字符串数组
       
       int execlp(const char *file, const char *arg, .../* (char  *) NULL */);
       file：可执行文件的文件名，文件名默认在系统环境变量PATH中寻找，如果给定文件路径名，则直接找这个文件，argv参数以NULL结尾。
       
       int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
       path：可执行文件的文件名，可以不包括路径名，用法与execl类似，只是要显示指定环境变量，环境变量位于命令行参数最后一个参数的后面。
       
        int execv(const char *path, char *const argv[]);
       path：可执行文件的文件名，可以不包括路径名，文件名默认在系统环境变量PATH中寻找，argv参数：用来提供给main函数的argv参数，且为一个以NULL结尾的字符串数组。
       
        int execvp(const char *file, char *const argv[]);
        file:可执行文件的文件名，该参数如果包含"/"，就相当于路径名；若不包含"/"，就到PATH环境变量定义的目录中寻找此文件。
        
        int execve(const char *path, char *const argv[],char *const envp[]);
        exec系列中唯一一个系统调用函数，path:将要执行程序的路径名，参数argv,envp与main函数的参数对应。




