#include<stdio.h>
#include<string.h>

int isPalindrome(char str[],int e)
{
    static int s=0;

    if(s==e)
        return 1;

    if(str[s]!=str[e])
        return 0;

    //printf("s & e is %d %d & e-s is %d\n",s,e,e-s);

    if(e-s>0)
    {
        ++s;
        isPalindrome(str,--e);
    }


    return 1;

}

int main()
{
    char st[150];
    scanf("%s",st);

    int len=strlen(st);

    int q=isPalindrome(st,len-1);

    if(q==1)
        printf("YES\n");
    else
        printf("NO\n");


    return 0;
}
