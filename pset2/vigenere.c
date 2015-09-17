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
    
    string key = (argv[1]);
    
    for(int chck = 0; chck < strlen(key);chck++)
    {
        if (!isalpha(key[chck]))
        {
        printf("Give me a string\n");
        return 1;
        } 
    }
    
   
    string msg = GetString();
 
    

    int k = 0;
     for (int i = 0, n = strlen(msg); i < n; i++)
        { 

         if (isalpha(msg[i]))
         {
             
            if (isupper(msg[i])) 
            {
                if (isupper((key[(k + strlen(key))%strlen(key)]))) 
                {
            
                printf("%c",(msg[i] - 65 + (key[(k + strlen(key))%strlen(key)] % 65))%26 + 65);
                k++;
                }
                else //(islower(key[i]))
                {
            printf("%c",(msg[i] - 65 + (key[(k + strlen(key))%strlen(key)]%97))%26 + 65); 
                k++;  
                }
            
            }
            else //(islower(msg[i])) 
            {
                if (isupper((key[(k + strlen(key))%strlen(key)])))
                {
            printf("%c",(msg[i] - 97 + (key[(k + strlen(key))%strlen(key)]%65))%26 + 97);
                k++;
                }
                
                else
                {
            printf("%c",(msg[i] - 97 + (key[(k + strlen(key))%strlen(key)]%97))%26 + 97);
                k++;   
                }
            }
        }   
        else
        {
        printf("%c",msg[i]);
        }
        
        }
        

    printf("\n");
        }

  
    //printf("%s\n", key); 
    //printf("%s\n", msg);  
    
    






