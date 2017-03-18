#include <stdio.h>
#include <stdlib.h>

long recPOWER(int x, int y)
{
    if(y==1)
        return x;
    else
        return x*recPOWER(x,y-1);
}
int main()
{
    int x=0,y=1;
    long power;
    printf("Enter integer base: \n ");
    scanf("%d",&x);
    printf("Enter integer power: \n ");
    scanf("%d",&y);

    if(y>=1)
    {
        printf("Valid Enter\n");
        power=recPOWER(x,y);
        printf("power of %d is %d",x,power);
    }
    else
    {
        printf("Invalid Enter");
    }
    return 0;
}
