#include<stdio.h>
#include<math.h>

int main()
{
    int ax,ay,bx,by,cx,cy;
    scanf("%d %d %d %d %d %d",&ax,&ay,&bx,&by,&cx,&cy);

    double a = sqrt((bx-cx)*(bx-cx)+(by-cy)*(by-cy));
    double b = sqrt((ax-cx)*(ax-cx)+(ay-cy)*(ay-cy));
    double c = sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));

    double s = (a+b+c)/2.0;

    double area = sqrt(s*(s-a)*(s-b)*(s*c));

    if(area==0)
        printf("Invalid Triangle");

    else
    {
        if(a==b && a==c)
            printf("Equilateral");
        else if(a!=b && b!=c && c!=a)
            printf("Scalene");
        else
            printf("Isosceles");
    }

    return 0;
}
