#include<stdio.h>
#include<string.h>
int fun(char s[50])
{
	char a[32][30]={"auto" , "break" , "case" , "char", "const" ,"continue", "default", "do", "double" ,"else" , "enum" , "extern", "float" ,"for", "goto", "if", "int", "long", "register", "return",  "short",  "signed",  "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile","while"};
        int i,k;
	for(i=0;i<32;i++)
	{
		if(strcmp(s,a[i])==0)
			return 0;
	}
	return 1;
}

int main()
{
    char s[51];
    int n,i,k;
    scanf("%d",&n);
    getchar( );
    while(n--)
    {
	
        gets(s);
        if( (s[0]=='_' || (s[0]<='z' && s[0]>='a') || (s[0]<='Z' && s[0]>='A' ))   && fun(s)==1)
        {
	    k=0;
            for(i=0;i<strlen(s);i++)
            {
                if( s[i]=='_' || (s[i]<='z' && s[i]>='a') || (s[i]<='Z' && s[i]>='A' ) || (s[i]<='9' && s[i]>='0')    )
                	k=0;
		else
		{
			  k=1;break;
		}
            }
            if(k==0)
                printf("yes\n");
            else
                printf("no\n");
        }
        else
            printf("no\n");
    }
}
