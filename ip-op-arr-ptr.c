#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   main()
  {
  char arr[3][8];
  char *ptr[3];
  int i;

   for(i=0;i<3;i++)
   {
      ptr[i]=arr[i];

   }
   for(i=0;i<3;i++){

      // gets(ptr[i]);
       scanf("%s",ptr[i]);


   }
   for(i=0;i<3;i++){
   // puts(ptr[i]);
    printf("%s",ptr[i]);

   }
  }

