#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            middle = (int)round((float)(image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3);
            image[h][w].rgbtBlue = middle;
            image[h][w].rgbtGreen = middle;
            image[h][w].rgbtRed = middle;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, new_red, green, new_green, blue, new_blue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            red = image[h][w].rgbtRed;
            green = image[h][w].rgbtGreen;
            blue = image[h][w].rgbtBlue;
            new_red = (int)round(0.393 * red + 0.769 * green + 0.189 * blue);
            new_green = (int)round(0.349 * red + 0.686 * green + 0.168 * blue);
            new_blue = (int)round(0.272 * red + 0.534 * green + 0.131 * blue);
            image[h][w].rgbtRed = (new_red > 255) ? 255 : new_red;
            image[h][w].rgbtGreen = (new_green > 255) ? 255 : new_green;
            image[h][w].rgbtBlue = (new_blue > 255) ? 255 : new_blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            buffer[w] = image[h][w];
        }
        for (int f = 0; f < width; f++)
        {
            image[h][f] = buffer[width - f - 1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    int new_red, new_green, new_blue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            buffer[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h - 1 < 0)
            {
                if (w - 1 < 0)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h + 1][w + 1].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed) / 4);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h + 1][w + 1].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen) / 4);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h + 1][w + 1].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue) / 4);
                }
                else if (w + 1 == width)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h + 1][w - 1].rgbtRed) / 4);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h + 1][w - 1].rgbtGreen) / 4);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h + 1][w - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed
                                                     + buffer[h + 1][w - 1].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h + 1][w + 1].rgbtRed) / 6);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen
                                                       + buffer[h + 1][w - 1].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h + 1][w + 1].rgbtGreen) / 6);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue
                                                      + buffer[h + 1][w - 1].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h + 1][w + 1].rgbtBlue) / 6);
                }
            }
            else if (h + 1 == height)
            {
                if (w - 1 < 0)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h - 1][w + 1].rgbtRed) / 4);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h - 1][w + 1].rgbtGreen) / 4);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h - 1][w + 1].rgbtBlue) / 4);
                }
                else if (w + 1 == width)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h - 1][w - 1].rgbtRed) / 4);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h - 1][w - 1].rgbtGreen) / 4);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h - 1][w - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed
                                                     + buffer[h - 1][w - 1].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h - 1][w + 1].rgbtRed) / 6);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen
                                                       + buffer[h - 1][w - 1].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h - 1][w + 1].rgbtGreen) / 6);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue
                                                      + buffer[h - 1][w - 1].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h - 1][w + 1].rgbtBlue) / 6);
                }
            }
            else
            {
                if (w - 1 < 0)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h - 1][w + 1].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed
                                                     + buffer[h + 1][w + 1].rgbtRed) / 6);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen
                                                       + buffer[h - 1][w + 1].rgbtGreen
                                                       + buffer[h + 1][w + 1].rgbtGreen) / 6);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue
                                                      + buffer[h - 1][w + 1].rgbtBlue
                                                      + buffer[h + 1][w + 1].rgbtBlue) / 6);
                }
                else if (w + 1 == width)
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h - 1][w - 1].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h + 1][w - 1].rgbtRed) / 6);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h - 1][w - 1].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h + 1][w - 1].rgbtGreen) / 6);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h - 1][w - 1].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h + 1][w - 1].rgbtBlue) / 6);
                }
                else
                {
                    image[h][w].rgbtRed = (int)round((float)(buffer[h][w].rgbtRed
                                                     + buffer[h - 1][w - 1].rgbtRed
                                                     + buffer[h - 1][w].rgbtRed
                                                     + buffer[h - 1][w + 1].rgbtRed
                                                     + buffer[h][w - 1].rgbtRed
                                                     + buffer[h][w + 1].rgbtRed
                                                     + buffer[h + 1][w - 1].rgbtRed
                                                     + buffer[h + 1][w].rgbtRed
                                                     + buffer[h + 1][w + 1].rgbtRed) / 9);

                    image[h][w].rgbtGreen = (int)round((float)(buffer[h][w].rgbtGreen
                                                       + buffer[h - 1][w - 1].rgbtGreen
                                                       + buffer[h - 1][w].rgbtGreen
                                                       + buffer[h - 1][w + 1].rgbtGreen
                                                       + buffer[h][w - 1].rgbtGreen
                                                       + buffer[h][w + 1].rgbtGreen
                                                       + buffer[h + 1][w - 1].rgbtGreen
                                                       + buffer[h + 1][w].rgbtGreen
                                                       + buffer[h + 1][w + 1].rgbtGreen) / 9);

                    image[h][w].rgbtBlue = (int)round((float)(buffer[h][w].rgbtBlue
                                                      + buffer[h - 1][w - 1].rgbtBlue
                                                      + buffer[h - 1][w].rgbtBlue
                                                      + buffer[h - 1][w + 1].rgbtBlue
                                                      + buffer[h][w - 1].rgbtBlue
                                                      + buffer[h][w + 1].rgbtBlue
                                                      + buffer[h + 1][w - 1].rgbtBlue
                                                      + buffer[h + 1][w].rgbtBlue
                                                      + buffer[h + 1][w + 1].rgbtBlue) / 9);
                }
            }
        }
    }


    return;
}
