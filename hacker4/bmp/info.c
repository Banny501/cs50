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
    if (argc != 2)
    {
        printf("Usage: ./info infile\n");
        return 1;
    }

    char* infile = argv[1];

    // remember filenames and coefficient

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
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
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    printf("bf.type %d\n", bf.bfType);
    printf("bf.size %d\n", bf.bfSize);
    printf("bf.bfReserved1 %d\n", bf.bfReserved1);
    printf("bf.bfReserved2 %d\n", bf.bfReserved2);
    printf("bf.bfOffBits %d\n", bf.bfOffBits);

    printf("\n");

    printf("bi.size %d\n", bi.biSize);
    printf("bi.Width %d\n", bi.biWidth);
    printf("bi.Height %d\n", bi.biHeight);
    printf("bi.biPlanes %d\n", bi.biPlanes);
    printf("bi.biBitCount %d\n", bi.biBitCount);
    printf("bi.biCompression %d\n", bi.biCompression);
    printf("bi.biSizeImage %d\n", bi.biSizeImage);
    printf("bi.x %d\n", bi.biXPelsPerMeter);
    printf("bi.y %d\n", bi.biYPelsPerMeter);
    printf("bi.biClrUsed %d\n", bi.biClrUsed);
    printf("bi.biClrImportant %d\n", bi.biClrImportant);

    // close infile
    fclose(inptr);
    // close outfile

    return 0;
}
