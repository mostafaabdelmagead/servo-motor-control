#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct employee
{
	int code; char name[10]; int age,overtime;
	float salary, deduct,tax;
}em;

float    ns[10];
    int i;
    em E[10];
//    for ( i = 0 ; i < 10 ; i++)
		//E[i].age = -1;

    void New (){


//while(1)
	//{
	    clrscr();
		do
		{
			printf("Please Enter Employee index from 1 to 10 (0 to end entering data) : ");
			scanf("%d",&i);
		}while( (i < 0 ) || ( i > 10 ));
		//if ( i == 0 )	break;

    gotoxy(2,2); printf("Name : ");
    gotoxy(2,4); printf("code : ");
    gotoxy(2,6); printf("Age : ");
    gotoxy(2,8); printf("Salary : ");
    gotoxy(2,10); printf("Deduction : ");
    gotoxy(2,12); printf("Tax : ");
    gotoxy(2,14); printf("Over time : ");

    gotoxy(10,2); scanf("%s",&E[i].name);
    gotoxy(10,4); scanf("%d",&E[i].code);
    gotoxy(10,6); scanf("%d",&E[i].age);
    gotoxy(10,8); scanf("%f",&E[i].salary);
    gotoxy(15,10); scanf("%f",&E[i].deduct);
    gotoxy(10,12); scanf("%f",&E[i].tax);
    gotoxy(12,14); scanf("%d",&E[i].overtime);


    //}
    for ( i = 0 ; i < 10 ; i++)
	{

        ns[i]= E[i].salary-E[i].deduct+E[i].overtime;

	}
	clrscr();


             }


       void Display(){
            clrscr();

//while(E[i].age != -1)
  //  {

    printf("\n\nPlease Enter Employee index from 1 to 10 while 0 terminate program : ");
    scanf("%d",&i);
    clrscr();
    switch(i)
    {
    case 1:
    if(E[1].age==-1) printf("invalid empolyee");
    else
             printf("Employee <1> Code is : %d\n\nEmployee Name <1> is : %s\n\nEmployee<1> net Salary is : %f\n\n",E[1].code,E[1].name,ns[1]);
             break;
    case 2:
    if(E[2].age==-1) printf("invalid empolyee");
    else
             printf("Employee <2> Code is : %d\n\nEmployee Name <2> is : %s\n\nEmployee<2> net Salary is : %f\n\n",E[2].code,E[2].name,ns[2]);
           break;
    case 3:
             if(E[3].age==-1) printf("invalid empolyee");
             else
             printf("Employee <3> Code is : %d\n\nEmployee Name <3> is : %s\n\nEmployee<3> net Salary is : %f\n\n",E[3].code,E[3].name,ns[3]);
            break;
    case 4:
            if(E[4].age==-1) printf("invalid empolyee");
             else
             printf("Employee <4> Code is : %d\n\nEmployee Name <4> is : %s\n\nEmployee<4> net Salary is : %f\n\n",E[4].code,E[4].name,ns[4]);
            break;

    case 5:
            if(E[5].age==-1) printf("invalid empolyee");
             else
             printf("Employee <5> Code is : %d\n\nEmployee Name <5> is : %s\n\nEmployee<5> net Salary is : %f\n\n",E[5].code,E[5].name,ns[5]);
            break;

    case 6:
            if(E[6].age==-1) printf("invalid empolyee");
             else
             printf("Employee <6> Code is : %d\n\nEmployee Name <6> is : %s\n\nEmployee<6> net Salary is : %f\n\n",E[6].code,E[6].name,ns[6]);
            break;

   case 7:

            if(E[7].age==-1) printf("invalid empolyee");
             else
             printf("Employee <7> Code is : %d\n\nEmployee Name <7> is : %s\n\nEmployee<7> net Salary is : %f\n\n",E[7].code,E[7].name,ns[7]);
            break;

   case 8:
            if(E[8].age==-1) printf("invalid empolyee");
             else
             printf("Employee <8> Code is : %d\n\nEmployee Name <8> is : %s\n\nEmployee<8> net Salary is : %f\n\n",E[8].code,E[8].name,ns[8]);
            break;

   case 9:
            if(E[9].age==-1) printf("invalid empolyee");
             else
             printf("Employee <9> Code is : %d\n\nEmployee Name <9> is : %s\n\nEmployee<9> net Salary is : %f\n\n",E[9].code,E[9].name,ns[9]);
            break;
   case 10:
   if(E[10].age==-1) printf("invalid empolyee");
             else
             printf("Employee <10> Code is : %d\n\nEmployee Name <10> is : %s\n\nEmployee<10> net Salary is : %f\n\n",E[10].code,E[10].name,ns[10]);
            break;
            break;

    }
   // }
       }


         void main(void)
           {



               char menu[3][10]={"New","Display","Exit"},ch;
               int i,current=0,exitflage=0;

        for ( i = 0 ; i < 10 ; i++)
		E[i].age = -1;

               do
               {
                 textattr(0x07);
                 //clrscr();
                   for(i=0;i<3;i++)
                   {
                       if(i==current)   textattr(0x70);
                       gotoxy(20,10+i*3);
                       cprintf("%s",menu[i]);
                       textattr(0x08);
                   }
                   ch=getch();
                   switch(ch)
                   {
                   case 0: ch=getch();
                        switch(ch)
                            {
                                case 72:
                                    current--;
                                    if(current<0)   current=2;
                                    break;
                                case 80 :
                                    current++;
                                    if(current>2)   current=0;
                                    break;
                                case 71 :
                                    current=0;
                                    break;
                                case 79 :
                                    current=2;  break;

                            }
                            break;
                                case 13 :
                                    switch(current)
                                    {
                                        case 0 :New(); break;
                                        case 1 : Display(); break;
                                        case 2 : exitflage=1; break;
                                    }
                                    break;
                                 case 27 :
                                    exitflage=1;
                                    printf("exit"); break;

                   }

               } while(exitflage != 1);
           }

