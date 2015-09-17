#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc,string argv[])
{


    if (argc != 2) 
    {
    printf("You didn't give me a key.\n");
    return 1;
    }
    
    else 
    {
    string msg = GetString();
    string key = (argv[1]); 
    
     
    for (int i = 0, n = strlen(msg); i < n; i++)
        {
        printf("%i ", (key[(i + strlen(key))%strlen(key)]));
        printf("%c ", msg[i]);
        printf("%c ", key[i]);
        if (isalpha(msg[i]))   
         
             
            if (isupper(msg[i])) 
            {

            printf("  %c\n",(msg[i] - 65 + (key[(i + strlen(key))%strlen(key)])%26 + 65));
     
            
            }
            else //(islower(msg[i])) 
            {
                if (isupper(key[i])) 
                {
            printf("%c",(msg[i] - 97 + (key[(i + strlen(key))%strlen(key)]%65))%26 + 97);
                }
                else
                {
            printf("%c",(msg[i] - 97 + (key[(i + strlen(key))%strlen(key)]%97))%26 + 97);   
                }
            }   
        else
        {
        printf("%c",msg[i]);
        }
        
        }
    printf("\n");
        }
} 
  
    //printf("%s\n", key); 
    //printf("%s\n", msg);  
    
    






