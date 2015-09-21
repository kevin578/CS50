#include <cs50.h>
#include <stdio.h>

int main (int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Not enough command line argumenets\n");
    }
    int x = atoi(argv[1]);
    printf("%d\n", x); 
}

