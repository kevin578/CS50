#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc,string argv[])
{
int key = atoi(argv[1]);

    if (argc == 2)
    {
    //printf("Please give me a string\n");
    string msg = GetString();
    

    for (int i = 0, n = strlen(msg); i < n; i++)
        {
        if (isalpha(msg[i]))   
        { 
            
            if (isupper(msg[i])) 
            {
            printf("%c",(((msg[i] - 65 + key)%26) + 65));
            }
            
            else //(islower(msg[i])) 
            {
            printf("%c",(((msg[i] - 97 + key)%26) + 97));
            }
        }   
        else
        {
        printf("%c",msg[i]);
        }

        }
    printf("\n");
}
    else 
    {
    printf("You didn't give me a key.\n");
    }
}

