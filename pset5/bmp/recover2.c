/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(void)
{
    FILE* disc = fopen("card.raw", "r");
    
    if (disc == NULL)
    {
        fclose(disc);
        printf("Couldn't open\n");
        return 2;
    }


    BYTE buffer[512] = {};
    
    FILE* writejpg = NULL; 
    bool searching = true;
    int counter = 0; 

    while (searching == true)
    {
        fread(&buffer, sizeof(buffer), 1, disc);
        
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer [2] == 0xff) && (buffer [3] == 0xe0))
        {   
        
            while (searching == true)
            {
            
            if (writejpg != NULL)       
            {
              fclose(writejpg);
            }
            
            //Name the new file
            char makejpg[9] = {};
            sprintf(makejpg, "%03d.jpg\n", counter);
            
            //Open file to write
            writejpg = fopen(makejpg, "w");  

            //Continue to write file while looking for new jpg file
            fwrite(&buffer, sizeof(buffer), 1, writejpg);
            bool found_newjpg = false;
            
            while (found_newjpg == false)
            {
                fread(&buffer, sizeof(buffer), 1, disc);
                fwrite(&buffer, sizeof(buffer), 1, writejpg);
                
                if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer [2] == 0xff) && (buffer [3] == 0xe0))
                {
                    found_newjpg = true;
                    
                }
                elseif()
            }
            
            
            counter++; 
 
            if (counter > 48)
            {
            searching = false;    
            fclose(disc);
            fclose(writejpg);
            return 0;
            } 
            }
            }        

    }
  
 }
    
    
    
    
    
    
    
    
    

