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

int main(void)
{
    //open file and check if it's null or not
    FILE* disc = fopen("card.raw", "r");
    
    if (disc == NULL)
    {
        fclose(disc);
        printf("Couldn't open\n");
        return 2;
    }

    //create buffer and file pointer to write jgps to
    uint8_t buffer[512] = {};
    
    FILE* writejpg = NULL;
    
    bool file_end = false;
    bool first_jpg_search = true; 
    bool searching = true;
    int counter = 0; 

    //search for initial jpg image
    while (first_jpg_search == true)
    {
        fread(&buffer, sizeof(buffer), 1, disc);
        
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer [2] == 0xff) && (buffer [3] == 0xe0))
        {
        first_jpg_search = false;
        }   
    }
    
    //loop to create all the jpgs and find the rest
    while (searching == true)
    {  
    
       //close any jpg files that are open 
       if (writejpg != NULL)       
           {
              fclose(writejpg);
           }
            
            //name the new file
            char makejpg[9] = {};
            sprintf(makejpg, "%03d.jpg", counter);
            
            
            //open file to write and write the block that has already been read
            writejpg = fopen(makejpg, "w");  
            fwrite(&buffer, sizeof(buffer), 1, writejpg);
 
            //read data from the card then write to a new jpg
            bool found_newjpg = false;
            while (found_newjpg == false)
            {
                fread(&buffer, sizeof(buffer), 1, disc);

                
                //check for the start of a new jpg or the end of the stream 
                if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer [2] == 0xff) && (buffer [3] == 0xe0))
                {
                    found_newjpg = true;
                }
                if (feof(disc))
                {
                    file_end = true;
                    searching = false;    
                    fclose(writejpg);
                    fclose(disc);
                    return 0;
                }
                
                if (found_newjpg == false)
                {
                fwrite(&buffer, sizeof(buffer), 1, writejpg);
                }
            }
            
            //increase counter
            counter++; 
     }
 }
    
    
    
    
    
    
    
    
    

