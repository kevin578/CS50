#include <stdio.h>
#include <cs50.h>


int main (void)
  {
  
  int x;
  do 
  {
  
  printf("How tall do you want your pyramid to be? Pick a number 1 - 23.\n"); 
  x = GetInt();
    
    if (x > 23)
    {
    printf ("Make your pyramid smaller, please.\n");
    }
  
    if (x < 0)
    {
    printf ("Your pyramid can't go underground!\n");
    }
    
    if (x == 0)
    {
    printf ("You can't have a flat pyramid!\n");
    }
  }
  
  while (x < 1 || x > 23);
  
  
  for (int i = 0; i < x;i++) 
    {
    
        for (int s = 0;s < 21 - i;s++) 
        {
         printf(" "); 
        }
        //21 spaces 
        //for (a = 2; a    
        //2 hashes
        
        for (int h = 0;h < i + 2; h++ )
        {
        printf ("#");
        }
     
     printf("\n");
        }
  
  
 } 

