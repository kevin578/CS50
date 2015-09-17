/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies and resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    // Get resize value
    
    int reSize = atoi(argv[1]);

    if (reSize <= 0 || reSize >= 100)
    {
        printf("Invalid resize value\n");
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER

    BITMAPFILEHEADER bf;

    
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // get padding for small image

    int small_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change width and height
    
    bi.biWidth = bi.biWidth * reSize;
    bi.biHeight = bi.biHeight * reSize;
    
    // record old width and height
    int old_width = bi.biWidth / reSize;
    int old_height = abs(bi.biHeight)/ reSize;
    
    
    // get large padding
     
    int large_padding = 0;
    
        if ((bi.biWidth + 4)% 4 == 0)
        {
        large_padding = 0;
        }
        else if ((bi.biWidth + 4) % 4 == 1)
        {
        large_padding = 3;
        }
        else if ((bi.biWidth + 4) % 4 == 2)
        {
        large_padding = 2;
        }
        else if ((bi.biWidth + 4) % 4 == 3)
        {
        large_padding = 1;
        }
    
    // get new sizes
    
    bi.biSizeImage = abs(bi.biHeight) * bi.biWidth + large_padding;
    bf.bfSize = 54  + (abs(bi.biHeight) * sizeof(RGBTRIPLE)) + (bi.biWidth * sizeof(RGBTRIPLE))+
    (large_padding * sizeof(RGBTRIPLE) * abs(bi.biHeight));
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    
    // iterate over infile's scanlines
   
    for (int a = 0; a < old_height; a++)
    {
        // iterate over pixels in scanline
            
                
        for (int vertical_scan = 0; vertical_scan < reSize; vertical_scan++)
        {

        
        fseek(inptr, 54 + (a * old_width * sizeof(RGBTRIPLE)) + (small_padding * a), SEEK_SET);
        
        for (int j = 0; j < old_width; j++)
         
        {

            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr); 

        
        for (int horizontal_scan = 0; horizontal_scan < reSize; horizontal_scan++)
        {  
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

        }
        
        if (j == old_width - 1)
        {
                  
        // skip over padding, if any
        /*fseek(inptr, small_padding, SEEK_CUR);
                
        // then add it back (to demonstrate how)
        
        for (int k = 0; k < large_padding; k++)
        {
            fputc(0x00, outptr);
        }*/     
        }
        }   

        }

     }
     


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
