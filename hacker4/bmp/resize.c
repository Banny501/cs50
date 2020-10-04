/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize a BMP file, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize coefficient infile outfile\n");
        return 1;
    }

    int coefficient = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (coefficient<=0||coefficient>100) {
      printf("Enter correct coefficient less than 100 and more than 0!\n");
      return 1;
    }

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

    // remember old padding
    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // set new Width adn Height
    int Width = bi.biWidth;
    int Height = abs(bi.biHeight);
    bi.biWidth *=coefficient;
    bi.biHeight *= coefficient;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // set new size
    bf.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+abs(bi.biHeight)*(bi.biWidth*3+padding);
    bi.biSizeImage = abs(bi.biHeight)*(bi.biWidth*3+padding);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // flag for seek when we draw string
    int flag = 0;

    for (size_t k = 0; k < Height; k++)
    {
      flag = 0;

      for (size_t i = 0; i < coefficient; i++)
      {
          if (flag)
          fseek(inptr, -(Width*sizeof(RGBTRIPLE)+old_padding), SEEK_CUR);

          for (size_t a = 0; a < Width; a++)
          {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (size_t t = 0; t < coefficient; t++)
              fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
          }

          fseek(inptr, old_padding, SEEK_CUR);

          for (size_t g = 0; g < padding; g++)
            fputc(0x00, outptr);

          flag ++;
      }
    }

    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // that's all folks
    return 0;
}
