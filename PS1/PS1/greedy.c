#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{

float money;
int coincount;
int quarters;
int dimes;
int nickels;
int total;

   do {
    printf ("How much change is owed?");
    money = GetFloat();
      } 
   while (money < 0);
   

coincount = round(money * 100);

quarters = 0;

    while (coincount >= 25)
        {
        (coincount -= 25);
        quarters++;
        } 
dimes = 0;

    while (coincount >= 10)
        {
        (coincount -= 10);
        dimes++;
        } 
nickels = 0;

    while (coincount >= 5)
        {
        (coincount -= 5);
        nickels++;
        } 

total = (quarters + dimes + nickels + coincount);


//printf("%i \n", quarters);
//printf("%i \n", dimes);
//printf("%i \n", nickels);
//printf("%i \n", coincount);
printf("%i", total);
printf("\n");
}


