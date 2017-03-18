#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int i=1;
    int p;
    int a,len;
    int exitflag = 0;
    char str[11],ch;

    printf("WELCOME FOR LINE EDITOR \n");
    str[10]='\0';
    //str[0]='\0';
    do
    {
       // printf("%d   %d",i,len);
       if(i>11)
            i=11;
        gotoxy(i,10);
        p=0;
        ch=getche();

         switch(ch)
        {
        case NULL:

                ch=getch();
                switch(ch)
                {

                case 75:
                    gotoxy(1,10);
                    printf("%s",str);
                    gotoxy(i,10);
                    i--;p=1;
                    ch='\0';
                    break;
                case  77:
                    gotoxy(1,10);
                    printf("%s",str);
                    if(i<len+1){i++;}

                     p=1;
                     gotoxy(i,10);
                     ch='\0';

                    break;
                case 71:
                    gotoxy(1,10);
                    printf("%s",str);
                    p=1;i=1;
                    gotoxy(i,10);
                    ch='\0';
                    break;
                case 79:
                    gotoxy(1,10);
                    printf("%s",str);
                    p=1;i=len+1;
                    gotoxy(i,10);
                    ch='\0';
                    break;
                    }break;
        case  13:
             gotoxy(5,15);
            printf("%s",str);
            break;
        case  27:
             exitflag=1;
            break;
        default :
             a=ch;
            if(a>64&&a<129)
            {
                if(p==1){i--;}
                else
                    str[i-1]=a;
                    len=strlen(str);
             i++;}
             break;

        }

    }while(exitflag!=1);

    return 0;
}
