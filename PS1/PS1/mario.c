#include <stdio.h>
#include <cs50.h>


int main (void)
  {
  
  int x;
  do 
  {
  
  printf("How tall do you want the pyramid to be? Pick a number 1 - 23.\n"); 
  x = GetInt();
    
    if (x > 23)
    {
    printf ("Make your pyramid smaller, please.\n");
    }
  
    if (x < 0)
    {
    printf ("Your pyramid can't go underground!\n");
    }
    
    
  }
  
  while (x < 0 || x > 23);
  
  
  for (int i = 0; i < x;i++) 
    {
    
        for (int s = 2;s <= x - i;s++) 
        {
         printf(" "); 
        }
        
        
        for (int h = 1;h <= i + 2; h++ )
        {
        printf ("#");
        }
     
        printf("\n");
        }
        
        
  
  
 } 

