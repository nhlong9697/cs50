/**
 * Resize a bit-map file.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    int r = atoi(argv[1]);
    if ((r > 100) || (r<0))
    {
        printf("n must be positive and smaller or equal to 100\n");
        return 5;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    //declare a struct for outfile
    BITMAPFILEHEADER outbf = bf;
    BITMAPINFOHEADER outbi = bi;
    //changing size of the outfile
    outbi.biWidth *= r;
    outbi.biHeight *= r;
    //calculating padding equation for outfile and infile
    int outpadding = (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 ;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 ;
    //calculating value for metadata of the outfile when it is resized
    outbi.biSizeImage = (sizeof(RGBTRIPLE) * abs(outbi.biHeight) * outbi.biWidth) + (outbi.biWidth * outpadding);
    
    outbf.bfSize = outbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //set an offset value to move pointer the begining of a scanline
    int offset = bi.biWidth * sizeof(RGBTRIPLE) + padding;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //make multiple vertical
        for (int vertical_line = 0; vertical_line < r; vertical_line++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //write RGB triple to outfile
                for (int horizontal_line = 0; horizontal_line < r; horizontal_line++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // then add padding to outfile
            for (int k = 0; k < outpadding; k++)
            {
                fputc(0x00, outptr);
            }
            //move the cursor to back to the begining of the line that the outfile is copying
            fseek(inptr, -offset, SEEK_CUR);
        }
        //move the cursor in the infile to the next line
        fseek(inptr,offset, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
