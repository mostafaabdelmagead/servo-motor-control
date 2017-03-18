#include<stdio.h>
#include<conio.h>
#include<string.h>
void swap_pointer ( int *a , int *b );

void main(void)
{
	int x , y ;
	clrscr();
	printf("Please Enter Two Numbers to swap : ");
	scanf("%d",&x);
	scanf("%d",&y);


	swap_pointer ( &x , &y );
	printf("\nNumbers After Swaping by pointer : \nX = %d\nY = %d",x,y);
	getch();
}
void swap_pointer (int *a , int *b)
{
	int temp ;
	temp 	= *a ;
	*a 		= *b;
	*b		= temp;
}

